#include "sdram.h"

/*
 * SDRAM Initialization
 */
uint8_t BSP_SDRAM_Init(void) {

    /* Set SDRAM status to an error */
    sdramState = HAL_SDRAM_STATE_ERROR;

    /*Set Instance of SDRAM_HandleTypeDef to point to the SDRAM banks 5 and 6 (FMC_SDRAM_DEVICE) */
    sdramHandle.Instance = FMC_SDRAM_DEVICE;

    /* Set timing parameters for SDRAM in FMC_SDRAM_TimingTypeDef */
    Timing.LoadToActiveDelay    = 2;
    Timing.ExitSelfRefreshDelay = 9;
    Timing.SelfRefreshTime      = 5;
    Timing.RowCycleDelay        = 8;
    Timing.WriteRecoveryTime    = 4;
    Timing.RPDelay              = 2;
    Timing.RCDDelay             = 2;

    sdramHandle.Init.SDBank             = FMC_SDRAM_BANK1;
    sdramHandle.Init.ColumnBitsNumber   = FMC_SDRAM_COLUMN_BITS_NUM_9;
    sdramHandle.Init.RowBitsNumber      = FMC_SDRAM_ROW_BITS_NUM_13;
    sdramHandle.Init.MemoryDataWidth    = FMC_SDRAM_MEM_BUS_WIDTH_32; //not sure, could be 8,16,32
    sdramHandle.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
    sdramHandle.Init.CASLatency         = FMC_SDRAM_CAS_LATENCY_2; //this and below is unsure, might be based on timing
    sdramHandle.Init.WriteProtection    = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
    sdramHandle.Init.SDClockPeriod      = FMC_SDRAM_CLOCK_PERIOD_2;
    sdramHandle.Init.ReadBurst          = FMC_SDRAM_RBURST_ENABLE;
    sdramHandle.Init.ReadPipeDelay      = FMC_SDRAM_RPIPE_DELAY_0;

    /* Takes given parameters, initializes */
    BSP_SDRAM_MspInit();
    if(HAL_SDRAM_Init(&sdramHandle, &Timing) != HAL_OK) {
        sdramState = HAL_SDRAM_STATE_ERROR;
    } else {
        sdramState = HAL_SDRAM_STATE_READY;
    }

     /* Calls SDRAM initialization sequence */
    BSP_SDRAM_Init_Sequence();
    return sdramState;
}


/*
 * Initializes SDRAM MSP
 */
void BSP_SDRAM_MspInit(void) {
    /** FMC GPIO Configuration
        PE1   ------> FMC_NBL1
        PE0   ------> FMC_NBL0
        PG15   ------> FMC_SDNCAS
        PD0   ------> FMC_D2
        PD1   ------> FMC_D3
        PF0   ------> FMC_A0
        PF1   ------> FMC_A1
        PF2   ------> FMC_A2
        PF3   ------> FMC_A3
        PG8   ------> FMC_SDCLK
        PF4   ------> FMC_A4
        PH5   ------> FMC_SDNWE
        PH3   ------> FMC_SDNE0
        PF5   ------> FMC_A5
        PH2   ------> FMC_SDCKE0
        PD15   ------> FMC_D1
        PD10   ------> FMC_D15
        PD14   ------> FMC_D0
        PD9   ------> FMC_D14
        PD8   ------> FMC_D13
        PF12   ------> FMC_A6
        PG1   ------> FMC_A11
        PF15   ------> FMC_A9
        PG2   ------> FMC_A12
        PF13   ------> FMC_A7
        PG0   ------> FMC_A10
        PE8   ------> FMC_D5
        PG5   ------> FMC_BA1
        PG4   ------> FMC_BA0
        PF14   ------> FMC_A8
        PF11   ------> FMC_SDNRAS
        PE9   ------> FMC_D6
        PE11   ------> FMC_D8
        PE14   ------> FMC_D11
        PE7   ------> FMC_D4
        PE10   ------> FMC_D7
        PE12   ------> FMC_D9
        PE15   ------> FMC_D12
        PE13   ------> FMC_D10
    */
    GPIO_InitTypeDef gpio_init_structure;

    /* Enable FMC clock */
    __HAL_RCC_FMC_CLK_ENABLE();

    /* Enable GPIO clocks */
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();


    /* Common configurations */
    gpio_init_structure.Mode = GPIO_MODE_AF_PP;
    gpio_init_structure.Pull = GPIO_PULLUP;
    gpio_init_structure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    gpio_init_structure.Alternate = GPIO_AF12_FMC;


    /* GPIOG configuration */
    gpio_init_structure.Pin = SDRAM_SDCLK_PIN | SDRAM_SDNCAS_PIN | SDRAM_BA0_PIN | SDRAM_BA1_PIN | SDRAM_A10_PIN |
            SDRAM_A11_PIN | SDRAM_A12_PIN;
    HAL_GPIO_Init(GPIOG, &gpio_init_structure);

    /* GPIOH configuration */
    gpio_init_structure.Pin = SDRAM_SDCKE_PIN | SDRAM_SDNE_PIN | SDRAM_SDNWE_PIN;
    HAL_GPIO_Init(GPIOH, &gpio_init_structure);

    /* GPIOF configuration */
    gpio_init_structure.Pin = SDRAM_SDNRAS_PIN | SDRAM_A0_PIN | SDRAM_A1_PIN | SDRAM_A2_PIN | SDRAM_A3_PIN |
            SDRAM_A4_PIN | SDRAM_A5_PIN | SDRAM_A6_PIN | SDRAM_A7_PIN | SDRAM_A8_PIN | SDRAM_A9_PIN;
    HAL_GPIO_Init(GPIOF, &gpio_init_structure);

    /* GPIOE configuration */
    gpio_init_structure.Pin = SDRAM_LDQM_PIN | SDRAM_UDQM_PIN | SDRAM_D4_PIN | SDRAM_D5_PIN | SDRAM_D6_PIN |
            SDRAM_D7_PIN | SDRAM_D8_PIN | SDRAM_D9_PIN | SDRAM_D10_PIN | SDRAM_D11_PIN | SDRAM_D12_PIN;
    HAL_GPIO_Init(GPIOE, &gpio_init_structure);

    /* GPIOD configuration */
    gpio_init_structure.Pin = SDRAM_D0_PIN | SDRAM_D1_PIN | SDRAM_D2_PIN | SDRAM_D3_PIN | SDRAM_D13_PIN |
            SDRAM_D14_PIN | SDRAM_D15_PIN;
    HAL_GPIO_Init(GPIOD, &gpio_init_structure);
}


/*
 * SDRAM Initialization Sequence (See page 42 of datasheet)
 */
void BSP_SDRAM_Init_Sequence(void) {

    /* Apply power simultaneously to Vdd and Vddq */

    /* Assert and hold CKE at LVTTL logic LOW. Provide stable CLOCK signal */
    Command.CommandMode            = FMC_SDRAM_CMD_CLK_ENABLE;
    Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
    Command.AutoRefreshNumber      = 1; //TODO: check these values for commands
    Command.ModeRegisterDefinition = 0;
    //TODO: Find appropriate timeout for sending commands
    HAL_SDRAM_SendCommand(&sdramHandle, &Command, (uint32_t)0xFFFF);

    /* Wait at least 100μs prior to issuing any command */
    HAL_Delay(1); //takes ms

    /* Perform a PRECHARGE ALL command */
    Command.CommandMode            = FMC_SDRAM_CMD_PALL;
    Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
    Command.AutoRefreshNumber      = 1;
    Command.ModeRegisterDefinition = 0;
    HAL_SDRAM_SendCommand(&sdramHandle, &Command, (uint32_t)0xFFFF);

    /* Wait tRP time */
    // 66ns
    /* HAL_Delay(1); //takes ms */

    /* Issue an AUTO REFRESH command */
    Command.CommandMode            = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
    Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
    Command.AutoRefreshNumber      = 8;
    Command.ModeRegisterDefinition = 0;
    HAL_SDRAM_SendCommand(&sdramHandle, &Command, (uint32_t)0xFFFF);

    /* Issue an AUTO REFRESH command */

    __IO uint32_t tmpmrd = 0;
    /* SDRAM is now ready for mode register programming */
    tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1           |\
                        SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |\
                        SDRAM_MODEREG_CAS_LATENCY_2           |\
                        SDRAM_MODEREG_OPERATING_MODE_STANDARD |\
                        SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

    Command.CommandMode            = FMC_SDRAM_CMD_LOAD_MODE;
    Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
    Command.AutoRefreshNumber      = 1;
    Command.ModeRegisterDefinition = tmpmrd;

    //13. Wait at least t MRD time, during which only NOP or DESELECT commands are allowed.

    //TODO: See if setting the refresh counter is appropriate here
    /* Step 6: Set the refresh rate counter */
    /* (15.62 us x Freq) - 20 */
    HAL_SDRAM_ProgramRefreshRate(&sdramHandle, REFRESH_COUNT);

}



static void HAL_FMC_MspDeInit(void){
    __HAL_RCC_FMC_CLK_DISABLE();

    /** FMC GPIO Configuration
    PE1   ------> FMC_NBL1
    PE0   ------> FMC_NBL0
    PG15   ------> FMC_SDNCAS
    PD0   ------> FMC_D2
    PD1   ------> FMC_D3
    PF0   ------> FMC_A0
    PF1   ------> FMC_A1
    PF2   ------> FMC_A2
    PF3   ------> FMC_A3
    PG8   ------> FMC_SDCLK
    PF4   ------> FMC_A4
    PH5   ------> FMC_SDNWE
    PH3   ------> FMC_SDNE0
    PF5   ------> FMC_A5
    PH2   ------> FMC_SDCKE0
    PD15   ------> FMC_D1
    PD10   ------> FMC_D15
    PD14   ------> FMC_D0
    PD9   ------> FMC_D14
    PD8   ------> FMC_D13
    PF12   ------> FMC_A6
    PG1   ------> FMC_A11
    PF15   ------> FMC_A9
    PG2   ------> FMC_A12
    PF13   ------> FMC_A7
    PG0   ------> FMC_A10
    PE8   ------> FMC_D5
    PG5   ------> FMC_BA1
    PG4   ------> FMC_BA0
    PF14   ------> FMC_A8
    PF11   ------> FMC_SDNRAS
    PE9   ------> FMC_D6
    PE11   ------> FMC_D8
    PE14   ------> FMC_D11
    PE7   ------> FMC_D4
    PE10   ------> FMC_D7
    PE12   ------> FMC_D9
    PE15   ------> FMC_D12
    PE13   ------> FMC_D10
    */
    HAL_GPIO_DeInit(GPIOG, SDRAM_SDCLK_PIN | SDRAM_SDNCAS_PIN | SDRAM_BA0_PIN | SDRAM_BA1_PIN | SDRAM_A10_PIN | SDRAM_A11_PIN | SDRAM_A12_PIN);

    /* GPIOH configuration */
    HAL_GPIO_DeInit(GPIOH, SDRAM_SDCKE_PIN | SDRAM_SDNE_PIN | SDRAM_SDNWE_PIN);

    /* GPIOF configuration */
    HAL_GPIO_DeInit(GPIOF, SDRAM_SDNRAS_PIN | SDRAM_A0_PIN | SDRAM_A1_PIN | SDRAM_A2_PIN | SDRAM_A3_PIN | SDRAM_A4_PIN | SDRAM_A5_PIN | SDRAM_A6_PIN | SDRAM_A7_PIN | SDRAM_A8_PIN | SDRAM_A9_PIN);

    /* GPIOE configuration */
    HAL_GPIO_DeInit(GPIOE, SDRAM_LDQM_PIN | SDRAM_UDQM_PIN | SDRAM_D4_PIN | SDRAM_D5_PIN | SDRAM_D6_PIN | SDRAM_D7_PIN | SDRAM_D8_PIN | SDRAM_D9_PIN | SDRAM_D10_PIN | SDRAM_D11_PIN | SDRAM_D12_PIN);

    /* GPIOD configuration */
    HAL_GPIO_DeInit(GPIOD, SDRAM_D0_PIN | SDRAM_D1_PIN | SDRAM_D2_PIN | SDRAM_D3_PIN | SDRAM_D13_PIN | SDRAM_D14_PIN | SDRAM_D15_PIN);

}
