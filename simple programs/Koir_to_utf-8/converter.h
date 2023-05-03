
#include <iconv.h>

class Converter
{
   public: 
       void setCodes(const char to_code[], const char from_code[])
       {
          conv = iconv_open(to_code, from_code); 
       }
       
       void convert(char string[], size_t len_in)
       {
          char in[500];
          char out[500];
          //strcpy(in, string);
          memcpy(in, string, len_in);
          size_t len_out = sizeof(out);
          char *out_ic = out;
          char *in_ic = in;
          memset(&out, 0, sizeof(out));
          int res = iconv(conv, &in_ic, &len_in, &out_ic, &len_out);
          strcpy(string, out); 
       }
       
       void close() { iconv_close(conv); }
   private: 
      iconv_t conv; 
}; 
