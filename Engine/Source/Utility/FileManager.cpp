#include "Source/Utility/FileManager.hpp"

FileManager::FileManager()
{

}

FileManager::~FileManager()
{
	SaveFile();
}

bool FileManager::LoadFile(const String& InFileName)
{
	Payload.clear();
	FileName = InFileName;
	return Read();
}

bool FileManager::SaveFile()
{
	if (HasChanged)
	{
		HasChanged = false;
		return Write();
	}
	
	return true;
}

bool FileManager::Read()
{
	std::ifstream _FileStream;
	_FileStream.open(FileName.c_str(), std::ifstream::in | std::ifstream::out);
	
	if (_FileStream.is_open())
	{
		String _Ln = "";
		while (std::getline(_FileStream, _Ln))
		{
			std::pair<String, String> _KeyPair = ParseSingleLine(_Ln);
			
			if (!_KeyPair.first.empty())
			{
				Payload[_KeyPair.first] = _KeyPair.second;
			}
		}
		
		_FileStream.close();
		HasChanged = false;
		return true;
	}
	
	return false;
}

bool FileManager::Write() const
{
	std::vector<std::pair<String, String>> _File;
	std::ifstream _In(FileName);
	
	if (_In.is_open())
	{
		String _Ln = "";
		while (std::getline(_In, _Ln))
		{
			std::pair<String, String> KeyPair = ParseSingleLine(_Ln);
			
			if (!KeyPair.first.empty())
			{
				auto _T = Payload.find(KeyPair.first);
				if (_T != Payload.end())
				{
					KeyPair.second = _T->second;
				}
			}
			else
			{
				KeyPair.first = _Ln;
			}
			_File.push_back(KeyPair);
		}
	}
	else
	{
		for (auto _T = Payload.begin(); _T != Payload.end(); _T++)
		{
			_File.push_back(std::make_pair(_T->first, _T->second));
		}
	}
	
	_In.close();
	
	std::ofstream _Out(FileName);
	if (_Out.is_open())
	{
		for (auto _T = _File.begin(); _T != _File.end(); _T++)
		{
			_Out << _T->first;
			
			if (!_T->second.empty())
			{
				_Out << " = " << _T->second;
			}
			
			_Out << std::endl;
		}
		
		_Out.close();
		return true;
	}
	
	return false;
}

std::pair<String, String> FileManager::ParseSingleLine(const String& Line) const
{
	if (Line.size() > 0 && (Line[0] != '#') && Line[0] != ';')
	{
		size_t i = 0;
		
		while(std::isspace(Line[i], Locale))
		{
			i++;
		}
		
		const size_t _KeyStringStart = i;
		while(!std::isspace(Line[i], Locale) && Line[i] != '=')
		{
			i++;
		}
		
		const String _Key = Line.substr(_KeyStringStart, i - _KeyStringStart);
		while(std::isspace(Line[i], Locale) || Line[i] == '=')
		{
			i++;
		}
		
		const String _Value = Line.substr(i, Line.size() - i);
		
		return std::make_pair(_Key, _Value);
	}
	
	return std::make_pair(String(), String());
}

void FileManager::Log() const
{
	for (auto& Element : Payload)
	{
		std::cout << Element.first << " = " << Element.second << std::endl;
	}
	
	std::cout << std::endl << "Size: " << Payload.size() << std::endl;
}
