#ifndef __ENUM_H
#define __ENUM_H
#include <cstdint>
#include <unordered_map>
#include <boost/preprocessor/tuple/enum.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/algorithm/string/split.hpp>
#define ENUM_EXPAND(z,d,i,e) BOOST_PP_COMMA_IF(i) BOOST_PP_TUPLE_ELEM(2,0,e) = BOOST_PP_TUPLE_ELEM(2,1,e)
#define ENUM_VALUE(seq) BOOST_PP_SEQ_FOR_EACH_I(ENUM_EXPAND,-,seq)

#define _DECLARE_ENUM(EnumName, seq)\
    struct EnumName\
    {\
        enum type\
        {\
            ENUM_VALUE(seq)\
        };\
        static const std::string& ToString(type v);\
        static bool Parse(const std::string& value, type& v);\

#define DECLARE_ENUM(EnumName, seq) _DECLARE_ENUM(EnumName, seq) };
#define DECLARE_ENUM_EX(EnumName, seq) _DECLARE_ENUM(EnumName, seq)\
    static bool ParseEx(const std::string& value,int32_t& v);};

#define ENUM_TOSTR(z,d,i,e) case BOOST_PP_TUPLE_ELEM(2,0,e): { static const std::string v(BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(2,0,e))); return v; };
#define ENUM_PARSE(z,d,i,e) gString2Enum->insert(std::make_pair(BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(2,0,e)),BOOST_PP_TUPLE_ELEM(2,0,e)));
#define IMPLEMENT_ENUM(EnumName,seq) \
    const std::string& EnumName::ToString(EnumName::type v)\
    {\
        switch(v)\
        {\
            BOOST_PP_SEQ_FOR_EACH_I(ENUM_TOSTR, ~, seq)\
            default:\
            {\
                static const std::string UNKNOWN_VALUE("UnknowValue4#"#EnumName);\
                return UNKNOWN_VALUE;\
            }\
        }\
    }\
    bool EnumName::Parse(const std::string& value, EnumName::type& v)\
    {\
        static std::unordered_map<std::string,EnumName::type>* gString2Enum = nullptr;\
        static std::once_flag initMap;\
        std::call_once(initMap\
        ,[]()\
		{\
            gString2Enum = new std::unordered_map<std::string,EnumName::type>();\
            BOOST_PP_SEQ_FOR_EACH_I(ENUM_PARSE,~,seq)\
		});\
        auto itResult = gString2Enum->find(value);\
        if(gString2Enum->end() != itResult)\
        {\
            v = itResult->second;\
            return true;\
        }\
        return false;\
   }\

#define IMPLEMENT_ENUM_EX(EnumName, seq)\
    IMPLEMENT_ENUM(EnumName,seq)\
    bool EnumName::ParseEx(const std::string& value,int32_t& v)\
    {\
        std::vector<std::string> actions;\
        boost::algorithm::split(actions,value,[](char c) {return c=='|'; },boost::algorithm::token_compress_on);\
\
        v = 0;\
        for(auto& action : actions)\
        {\
            EnumName::type tmpAction;\
            if(Parse(action,tmpAction))\
            {\
                v |= tmpAction;\
            }\
            else\
            {\
                return false;\
            }\
        }\
\
        return true;\
    }

#endif
