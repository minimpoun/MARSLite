#pragma once

#include "string"
#include "TypeHelpers.hpp"
#include <map>
#include <vector>
#include <sstream>
#include <locale>
#include <fstream>

namespace MARS
{
/*
 * simple file managment class. Will handle things such as loading, saving and deleting .txt && .mars files off of the hard drive.
 * Make sure LoadFile() is called before anything else. You can also parse .mars settings files with this class. This is very lightweight
 * as file managers go and is missing a lot of features, but this is MARS Lite for a reason. 
 * 
 * There is no source file, it's all done in the header.
 */
class FileManager
{
public:

	FileManager();
	~FileManager();

	/*
	 * This should be the first function called. Other functions
	 * such as SaveFile() and HasFileChanged() will return false
	 * unless this function loaded a file before they werer called.
	 * 
	 * @Param FileName: The name and path of the file that will be loaded
	 * @Return: Whether or not the file was found and loaded
	 */
	bool LoadFile(const String& FileName);

	/*
	 * @Return: Whether or not the file was saved
	 */
	bool SaveFile();

	/*
	 * @Return: Whether or not the file was changed.
	 */
	bool HasFileChanged() const { return HasChanged; }

	// These templates are for parsing .mars settings files
	template<typename T>
	void Get(const String& Key, T& Value) const;

	template<typename T>
	void Get(const String& Key, std::vector<T>& ValuePair) const;

	template<typename T>
	void Set(const String& Key, std::vector<T> ValuePair);

	template<typename T>
	void Set(const String& Key, const T Value);

	void Log() const;

private:

	template<typename T>
	T ToType(const String& In) const;

	template<typename T>
	String ToString(const T In) const;

	bool Read();
	bool Write() const;

	std::pair<String, String> ParseSingleLine(const String& Line) const;

	bool HasChanged;
	String FileName;
	std::map<String, String> Payload;
	const std::locale Locale;
};

FileManager::FileManager()
{
	
}

FileManager::~FileManager()
{
	SaveFile();
}
















///////////////////////////////////////////
// implementation


template<typename T>
inline void FileManager::Get(const String& Key, T& Value) const
{
	auto _T = Payload.find(Key);
	if (_T != Payload.end())
	{
		Value = ToType<T>(_T->second);
	}
}

template<typename T>
inline void FileManager::Get(const String& Key, std::vector<T>& Value) const
{
	auto _T = Payload.find(Key);
	if (_T != Payload.end())
	{
		String _Out;
		std::istringstream _Stream(_T->second);

		Value.clear();

		while (getline(_Stream, _Out, ','))
		{
			Value.push_back(ToType<T>(_Out));
		}
	}
}

template<typename T>
inline void FileManager::Set(const String& Key, const T Value)
{
	Payload[Key] = ToString<T>(Value);
	HasChanged = true;
}

template<typename T>
inline void FileManager::Set(const String& Key, std::vector<T> Value)
{
	String _Str = "";
	for (size_t i = 0; i < Value.size() - 1; i++)
	{
		_Str += ToString<T>(Value.at(i)) + ",";
	}

	_Str += ToString<T>(Value.back());
	Payload[Key] = _Str;
	HasChanged = true;
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
	_FileStream.open(FileName.c_str(), std::ifstream::in);

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

// conversions //
template<typename T>
inline String FileManager::ToString(T in) const
{
	// only supporting few of the standard data types. Maybe in the future we can implement dynamic type conversion, /shrug
	// That sounds more like a thing for the full version of MARS tho
	throw "Unsupported Type";
}

template<>
inline String FileManager::ToString<String>(String In) const { return In; }

template<>
inline String FileManager::ToString<const char*>(const char* In) const { return String(In); }

template<>
inline String FileManager::ToString<bool>(bool In) const { return (In) ? "true" : "false"; }

template<>
inline String FileManager::ToString<char>(char In) const 
{
	std::stringstream _Stream;
	_Stream << In;
	return _Stream.str();
}

template<>
inline String FileManager::ToString<short>(short In) const
{
	std::stringstream _Stream;
	_Stream << In;
	return _Stream.str();
}

template<>
inline String FileManager::ToString<int>(int In) const
{
	std::stringstream _Stream;
	_Stream << In;
	return _Stream.str();
}

template<>
inline String FileManager::ToString<float>(float In) const
{
	std::stringstream _Stream;
	_Stream << In;
	return _Stream.str();
}

template<>
inline String FileManager::ToString<double>(double In) const
{
	std::stringstream _Stream;
	_Stream << In;
	return _Stream.str();
}

template<typename T>
inline T FileManager::ToType(const String& In) const
{
	std::cout << "Unsupported type" << std::endl;
}

template<>
inline String FileManager::ToType<String>(const String& In) const { return In; }

template<>
inline char FileManager::ToType<char>(const String& In) const
{
	return In[0];
}

template<>
inline short FileManager::ToType<short>(const String& In) const
{
	int T;
	std::stringstream _Stream(In);
	_Stream >> T;
	return T;
}

template<>
inline int FileManager::ToType<int>(const String& In) const
{
	int T;
	std::stringstream _Stream(In);
	_Stream >> T;
	return T;
}

template<>
inline float FileManager::ToType<float>(const String& In) const
{
	double T;
	std::stringstream _Stream(In);
	_Stream >> T;
	return T;
}

template<>
inline double FileManager::ToType<double>(const String& In) const
{
	double T;
	std::stringstream _Stream(In);
	_Stream >> T;
	return T;
}

template<>
inline bool FileManager::ToType<bool>(const String& In) const
{
	return In[0] == 't' ? true : false;
}

}