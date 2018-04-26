#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#define max_arg_len 20

#ifdef __WIN32
    #define kcp_name "kcptun.exe"
#else
    #define kcp_name "kcptun"
#endif // __WIN32


typedef struct options
{
    size_t num;
    char *keys[max_arg_len];
    char *values[max_arg_len];
} options_t;

int parse_options(char *str, size_t str_len, options_t *opts)
{
    int i, opt_idx;
    char p;

    i = 0;
    opt_idx = 0;
    p = '\0';

    if (str == NULL || str_len == 0)
        return -1;

    opts->keys[0] = str;

    while (opt_idx < max_arg_len
            && i < str_len && str[i] != '\0')
    {
        char c = str[i];
        switch (c)
        {
        case '\\':
            if (i + 1 == str_len)
                return -1;
            memmove(str + i, str + i + 1, str_len - i - 1);
            str_len--;
            str[str_len] = '\0';
            break;
        case ';':
            if (p != '\\')
            {
                str[i] = '\0';
                if (i + 1 < str_len)
                {
                    opt_idx++;
                    opts->keys[opt_idx] = str + i + 1;
                }
            }
            i++;
            break;
        case '=':
            if (p != '\\')
            {
                if (i + 1 == str_len)
                    return -1;
                str[i] = '\0';
                opts->values[opt_idx] = str + i + 1;
            }
            i++;
            break;
        default:
            i++;
            break;
        }
        p = c;
    }

    opts->num = opt_idx + 1;

    return opts->num;
}

const char*
get_opt(const char *key, options_t *opts)
{
    int i;
    for (i = 0; i < opts->num; i++)
    {
        if (strcmp(key, opts->keys[i]) == 0)
        {
            if (opts->values[i] != NULL)
                return opts->values[i];
            else
                return key;
        }
    }
    return NULL;
}
int main(int argc,char** argv)
{
    char *ss_remote_host                     = getenv("SS_REMOTE_HOST");
    char *ss_remote_port                     = getenv("SS_REMOTE_PORT");
    char *ss_local_host                      = getenv("SS_LOCAL_HOST");
    char *ss_local_port                      = getenv("SS_LOCAL_PORT");
    char *ss_plugin_opts                     = getenv("SS_PLUGIN_OPTIONS");

    if(ss_plugin_opts == NULL) return 0;
    ss_plugin_opts = strdup(ss_plugin_opts);
    options_t opts;
    int opt_num = parse_options(ss_plugin_opts,strlen(ss_plugin_opts), &opts);
    int i,j=0;
    char* cmd = malloc(sizeof(char)*200);

    j = sprintf(cmd,"%s ",kcp_name);
    j += sprintf(cmd+j,"-r %s:%s -l \":%s\" ",ss_remote_host,ss_remote_port,ss_local_port);

    for(i=0;i<opts.num;i++)
    {
        j += sprintf(cmd+j,"--%s %s ",opts.keys[i],opts.values[i]);
    }

    //MessageBoxA(0,cmd,"1",0);
    system(cmd);
    return 0;
}
