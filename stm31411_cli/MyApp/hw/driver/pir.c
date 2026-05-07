#include "pir.h"
#include "ap.h"
#include "main.h"

static bool     g_pir_enabled    = false;
static bool     g_pir_last_state = false;
static uint32_t g_pir_detect_ms  = 0;   // 감지 시작 시각
static uint32_t g_pir_last_log_s = 0;   // 마지막으로 출력한 초

void pirInit(void)
{
    g_pir_enabled    = false;
    g_pir_last_state = false;
    g_pir_detect_ms  = 0;
    g_pir_last_log_s = 0;
}

bool pirRead(void)
{
    return HAL_GPIO_ReadPin(PIR_GPIO_Port, PIR_Pin) == GPIO_PIN_SET;
}

void pirCheck(void)
{
    if (!g_pir_enabled) return;

    bool current = pirRead();
    uint32_t now = osKernelGetTickCount();

    if (current)
    {
        if (!g_pir_last_state)
        {
            // 감지 시작
            g_pir_detect_ms  = now;
            g_pir_last_log_s = 0;
            cliPrintf("[PIR] 동작 감지 시작!\r\n");
        }

        // 1초마다 경과 시간 출력
        uint32_t elapsed_s = (now - g_pir_detect_ms) / 1000;
        if (elapsed_s > g_pir_last_log_s)
        {
            g_pir_last_log_s = elapsed_s;
            cliPrintf("[PIR] 동작 감지 중... %lus\r\n", elapsed_s);
        }
    }
    else
    {
        if (g_pir_last_state)
        {
            // 감지 해제
            uint32_t total_s = (now - g_pir_detect_ms) / 1000;
            cliPrintf("[PIR] 동작 감지 해제 (총 %lus)\r\n", total_s);
            g_pir_detect_ms  = 0;
            g_pir_last_log_s = 0;
        }
    }

    g_pir_last_state = current;
}

void cliPir(uint8_t argc, char **argv)
{
    if (argc < 2)
    {
        cliPrintf("Usage: pir on\r\n");
        cliPrintf("       pir off\r\n");
        cliPrintf("       pir read\r\n");
        cliPrintf("       pir status\r\n");
        return;
    }

    if (strcmp(argv[1], "on") == 0)
    {
        g_pir_enabled    = true;
        g_pir_last_state = false;
        g_pir_detect_ms  = 0;
        g_pir_last_log_s = 0;
        cliPrintf("[PIR] 활성화됨\r\n");
    }
    else if (strcmp(argv[1], "off") == 0)
    {
        g_pir_enabled = false;
        cliPrintf("[PIR] 비활성화됨\r\n");
    }
    else if (strcmp(argv[1], "read") == 0)
    {
        cliPrintf("[PIR] 현재 상태: %s\r\n", pirRead() ? "감지됨" : "없음");
    }
    else if (strcmp(argv[1], "status") == 0)
    {
        cliPrintf("[PIR] enabled=%s  detecting=%s\r\n",
                  g_pir_enabled    ? "ON"  : "OFF",
                  g_pir_last_state ? "감지중" : "없음");
    }
    else
    {
        cliPrintf("Unknown command\r\n");
    }
}