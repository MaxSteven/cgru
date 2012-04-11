#include "name_af.h"

#include "msg.h"
#include "regexp.h"

#define AFOUTPUT
#undef AFOUTPUT
#include "../include/macrooutput.h"

char * af::jsonParseMsg( rapidjson::Document & o_doc, af::Msg * i_msg, std::string * o_err)
{
	int datalen = i_msg->dataLen();
	char * data = new char[datalen+1];
	memcpy( data, i_msg->data(), datalen);
	data[datalen] = '\0';

	std::string err;

	if( o_doc.ParseInsitu<0>(data).HasParseError())
	{
		err = "JSON: Parsing failed at character " + af::itos( int( o_doc.GetErrorOffset()));
		err += ":\n";
		err += o_doc.GetParseError();
		delete [] data;
		data = NULL;
	}

	if( false == o_doc.IsObject())
	{
		err = "JSON: Can't find root object.";
		delete [] data;
		data = NULL;
	}

	if( o_err )
		*o_err = err;
	else
		AFERRAR("%s", err.c_str())

	return data;
}

void af::jr_regexp( const char * i_name, RegExp & o_attr, const JSON & i_object, std::string * o_str)
{
	const JSON & value = i_object[i_name];
	if( false == value.IsString()) return;
	std::string pattern = (char*)value.GetString();
	bool ok = o_attr.setPattern( pattern);
	if( o_str == NULL )
		return;
	if( ok )
		*o_str += std::string("\n\"") + i_name + "\" set to \"" + pattern + "\"";
	else
		*o_str += std::string("\n\"") + i_name + "\" invalid pattern \"" + pattern + "\"";
}

void af::jr_string( const char * i_name, std::string & o_attr, const JSON & i_object, std::string * o_str)
{
	const JSON & value = i_object[i_name];
	if( false == value.IsString()) return;
	o_attr = (char*)value.GetString();
	if( o_str ) *o_str += std::string("\n\"") + i_name + "\" set to \"" + o_attr + "\"";
}

void af::jr_bool  ( const char * i_name, bool        & o_attr, const JSON & i_object, std::string * o_str)
{
	const JSON & value = i_object[i_name];
	if( false == value.IsBool()) return;
	o_attr = value.GetBool();
	if( o_str ) *o_str += std::string("\n\"") + i_name + "\" set to " + (o_attr?"true":"false") + "";
}

void af::jr_int8  ( const char * i_name, int8_t      & o_attr, const JSON & i_object, std::string * o_str)
{
	const JSON & value = i_object[i_name];
	if( false == value.IsInt()) return;
	o_attr = value.GetInt();
	if( o_str ) *o_str += std::string("\n\"") + i_name + "\" set to " + af::itos(o_attr) + "";
}

void af::jr_uint8 ( const char * i_name, uint8_t     & o_attr, const JSON & i_object, std::string * o_str)
{
	const JSON & value = i_object[i_name];
	if( false == value.IsUint()) return;
	o_attr = value.GetUint();
	if( o_str ) *o_str += std::string("\n\"") + i_name + "\" set to " + af::itos(o_attr) + "";
}

void af::jr_int16 ( const char * i_name, int16_t     & o_attr, const JSON & i_object, std::string * o_str)
{
	const JSON & value = i_object[i_name];
	if( false == value.IsInt()) return;
	o_attr = value.GetInt();
	if( o_str ) *o_str += std::string("\n\"") + i_name + "\" set to " + af::itos(o_attr) + "";
}

void af::jr_uint16( const char * i_name, uint16_t    & o_attr, const JSON & i_object, std::string * o_str)
{
	const JSON & value = i_object[i_name];
	if( false == value.IsUint()) return;
	o_attr = value.GetUint();
	if( o_str ) *o_str += std::string("\n\"") + i_name + "\" set to " + af::itos(o_attr) + "";
}

void af::jr_int32 ( const char * i_name, int32_t     & o_attr, const JSON & i_object, std::string * o_str)
{
	const JSON & value = i_object[i_name];
	if( false == value.IsInt()) return;
	o_attr = value.GetInt();
	if( o_str ) *o_str += std::string("\n\"") + i_name + "\" set to " + af::itos(o_attr) + "";
}

void af::jr_uint32( const char * i_name, uint32_t    & o_attr, const JSON & i_object, std::string * o_str)
{
	const JSON & value = i_object[i_name];
	if( false == value.IsUint()) return;
	o_attr = value.GetUint();
	if( o_str ) *o_str += std::string("\n\"") + i_name + "\" set to " + af::itos(o_attr) + "";
}

void af::jr_int64( const char * i_name, int64_t    & o_attr, const JSON & i_object, std::string * o_str)
{
	const JSON & value = i_object[i_name];
	if( false == value.IsInt64()) return;
	o_attr = value.GetInt64();
	if( o_str ) *o_str += std::string("\n\"") + i_name + "\" set to " + af::itos(o_attr) + "";
}

void af::jr_int32vec( const char * i_name, std::vector<int32_t> & o_attr, const JSON & i_object)
{
	const JSON & array = i_object[i_name];
	if( false == array.IsArray())
		return;

	for( int i = 0; i < array.Size(); i++)
		if( array[i].IsInt())
			o_attr.push_back( array[i].GetInt());
}
