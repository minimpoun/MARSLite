#pragma once

#include "Common.h"

/*
 * simple file management class. Will handle things such as loading, saving and deleting .txt && .mars files off of the hard drive.
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
	 * unless this function loaded a file before they were called.
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