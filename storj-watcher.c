#include <stdio.h>
#include <storj.h>

static void json_logger(const char *message, int level, void *handle)
{
  printf("{\"message\": \"%s\", \"level\": %i, \"timestamp\": %" PRIu64 "}\n",
message, level, storj_util_timestamp());
}

int main()
{
    storj_env_t *env = NULL;
    storj_http_options_t http_options = {
      .user_agent = "storj-watcher",
      .low_speed_limit = STORJ_LOW_SPEED_LIMIT,
      .low_speed_time = STORJ_LOW_SPEED_TIME,
      .timeout = STORJ_HTTP_TIMEOUT
    };

    storj_bridge_options_t options = {
      .proto = "https",
      .host = "api.storj.io",
      .port = 443,
      .user = NULL,
      .pass = NULL
    };

    storj_log_options_t log_options = {
      .logger = json_logger,
      .level = 4
    };

    env = storj_init_env(&options, NULL, &http_options, &log_options);


    printf("Hello\n");
    if (env) {
      storj_destroy_env(env);
    }
    return 0;
}
