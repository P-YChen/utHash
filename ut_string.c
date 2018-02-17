#include "Utstring.h"

UT_string *buf = NULL;

int main(void)
{
    utstring_new(buf);
    printf("[init str]: len=%d\n", utstring_len(buf));

    utstring_bincpy(buf,"hello",strlen("hello"));
    printf("[str <%d>]: buf=%s\n", utstring_len(buf), utstring_body(buf));

    utstring_printf(buf, "%s %d", __FILE__, __LINE__);
    printf("[str <%d>]: buf=%s\n", utstring_len(buf), utstring_body(buf));

    

    return 0;
}
