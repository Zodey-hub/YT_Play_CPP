#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <string>
#include <cstring>
#include <algorithm>

/**
 *  @brief  Get occurrence of the given string.
 *  @param source  String in which to search.
 *  @param string_to_find  String to count.
 *  @return  The number of occurrences as int.
 */
int get_occurrences(const std::string *source, const char *string_to_find)
{
    int occurrences = 0;
    std::string::size_type start = 0;

    while ((start = source->find(*string_to_find, start)) != std::string::npos)
    {
        occurrences++;
        start += strlen(string_to_find);
    }
    return occurrences;
}

/**
 *  @brief  Trim the given string.
 *  @param string_to_trim  String to trim.
 *  @return  Nothing, it will modify the param.
 */
void trim(std::string *string_to_trim)
{
    const char type_of_whitespaces[] = " \t\n\r\f\v";
    string_to_trim->erase(string_to_trim->find_last_not_of(type_of_whitespaces) + 1);
    string_to_trim->erase(0, string_to_trim->find_first_not_of(type_of_whitespaces));
}

/**
 *  @brief  Gives the text between two strings.
 *  @param source  String in which to search.
 *  @param before  String which is before the string you want to get.
 *  @param after  String which is after the string you want to get.
 *  @return  The text between the second and the third param.
 */
std::string give_text_between(const std::string *source, const char *before, const char *after)
{
    unsigned int start = source->find(before);
    start += strlen(before);
    unsigned int end = source->find(after, start);
    std::string between_text = source->substr(start, end - start);
    trim(&between_text);
    return between_text;
}

/**
 *  @brief  Gives the text between two strings.
 *  @param source  String in which to search.
 *  @param before  String which is before the string you want to get.
 *  @param after  String which is after the string you want to get.
 *  @return  The text between the second and the third param.
 */
std::string give_text_between(const std::string *source, const std::string *before, const std::string *after)
{
    unsigned int start = source->find(*before);
    start += before->length();
    unsigned int end = source->find(*after, start);
    std::string between_text = source->substr(start, end - start);
    trim(&between_text);
    return between_text;
}

#endif