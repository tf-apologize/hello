#include <iostream>  
#include <string.h>
using namespace std;

/**
@description 判断通配符与字符串是否匹配
@param [in]		pattern			通配符串
@param [in]		patternLen		通配符串长度
@param [in]		string			匹配字符串
@param [in]		stringLen		匹配字符串长度
@param [in]		nocase			是否忽略大小写（true:忽略  false:不忽略）
@return  bool	true:匹配	false:不匹配
**/
bool stringmatchlen(const char *pattern, int patternLen, const char *string, int stringLen, bool nocase)
{
	while(patternLen) 
	{
		switch(pattern[0]) 
		{
		case '*':		//*代表零个到多个任意字符
			while (pattern[1] == '*')	//通配符个*一起等同于单个*
			{
				pattern++;
				patternLen--;
			}
			if (patternLen == 1)		//通配符只有*，则直接返回
			{
				return true; /** match */
			}
				
			while(stringLen)	//循环向后匹配
			{
				//从下一个不为*的通配符向后匹配
				if (stringmatchlen(pattern + 1, patternLen - 1, string, stringLen, nocase))
				{
					return true; /** match */
				}
				
				//没有匹配上继续跳过字符（*代表零个到多个任意字符）
				string++;
				stringLen--;
			}
			return false; /** no match */
			break;
		case '?':		//?代表一个任意字符
			if (stringLen == 0)	//?必须匹配一个字符
			{
				return false; /** no match */
			}

			//匹配单个字符break
			string++;
			stringLen--;
			break;
		case '[':		//匹配字符范围
		{
			int inot, match;

			pattern++;
			patternLen--;
			inot = pattern[0] == '^';	//取反标志,如[^1-9]
			if (inot) 
			{
				pattern++;
				patternLen--;
			}
			match = 0;
			while(1) 
			{
				if (pattern[0] == '\\')			//转义字符
				{
					pattern++;
					patternLen--;
					if (pattern[0] == string[0])
						match = 1;
				}
				else if (pattern[0] == ']')		//范围结束标识
				{
					break;
				}
				else if (patternLen == 0) 
				{
					pattern--;
					patternLen++;
					break;
				}
				else if (pattern[1] == '-' && patternLen >= 3) 
				{
					int start = pattern[0];
					int end = pattern[2];
					int c = string[0];
					if (start > end)	//支持反序，如[1-9] <=> [9-1]
					{
						int t = start;
						start = end;
						end = t;
					}
					if (nocase)		//不区分大小写
					{
						start = tolower(start);
						end = tolower(end);
						c = tolower(c);
					}

					//跳过-和"-"后面的字符
					pattern += 2;
					patternLen -= 2;

					//字符是否在范围内
					if (c >= start && c <= end)
						match = 1;
				}
				else 
				{
					if (!nocase) 
					{
						if (pattern[0] == string[0])
							match = 1;
					}
					else 
					{
						if (tolower((int)pattern[0]) == tolower((int)string[0]))
							match = 1;
					}
				}
				pattern++;
				patternLen--;
			}
			if (inot)
				match = !match;
			if (!match)
				return 0; /** no match */
			string++;
			stringLen--;
			break;
		}
		case '\\':		//转义字符
			if (patternLen >= 2) 
			{
				pattern++;
				patternLen--;
			}
			/** fall through */
		default:	//单个字符完全匹配
			if (!nocase)	//区分大小写
			{
				if (pattern[0] != string[0])
					return 0; /** no match */
			}
			else			//不区分大小写
			{
				if (tolower((int)pattern[0]) != tolower((int)string[0]))
					return 0; /** no match */
			}

			//匹配单个字符break
			string++;
			stringLen--;
			break;
		}

		//通配符后移
		pattern++;
		patternLen--;

		if (stringLen == 0) 
		{
			while (*pattern == '*')		//跳过通配符末尾多个*
			{
				pattern++;
				patternLen--;
			}
			break;
		}
	}

	//通配符和字符串完全匹配结束
	if (patternLen == 0 && stringLen == 0)
	{
		return true;
	}

	return false;
}

/**
@description 判断通配符与字符串是否匹配
@param [in]		pattern		通配符串
@param [in]		string		匹配字符串
@param [in]		nocase		是否忽略大小写（true:忽略  false:不忽略）
@return  bool	true:匹配	false:不匹配
**/
bool stringmatch(const char *pattern, const char *string, bool nocase) {
	return stringmatchlen(pattern, strlen(pattern), string, strlen(string), nocase);
}

void Test(const char *pPattern, const char *pStr)
{
	if (stringmatch(pPattern, pStr, false))
	{
		fprintf(stderr, "合约代码[%s]符合TAS合约匹配规则[%s]\n", pStr, pPattern);
	}
	else
	{
		std::cout << "no" << std::endl;
	}
}
