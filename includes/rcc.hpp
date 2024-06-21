#include <stdint.h>
#include <rcc.h>

class rcc_t {
public:
    union {
        struct {
            uint32_t HSION:1;
            uint32_t HSIRDY:1;
            uint32_t Reserved1:1;
            uint32_t HSITRIM:5;
            uint32_t HSICAL:8;
            uint32_t HSEON:1;
            uint32_t HSERDY:1;
            uint32_t HSEBYP:1;
            uint32_t CSSON:1;
            uint32_t Reserved2:4;
            uint32_t PLLON:1;
            uint32_t PLLRDY:1;
            uint32_t PLLI2SON:1;
            uint32_t PLLI2SRDY:1;
            uint32_t Reserved3:4;
        }CR;
        uint32_t REG_CR;
    };

    union {
        struct {
            uint32_t PLLM:6;
            uint32_t PLLN:9;
            uint32_t Reserved1:1;
            uint32_t PLLP:2;
            uint32_t Reserved2:4;
            uint32_t PLLSRC:1;
            uint32_t Reserved3:1;
            uint32_t PLLQ:4;
            uint32_t Reserved4:4;
        }PLLCFGR;
        uint32_t REG_PLLCFGR;
    };

    union {
        struct {
            uint32_t SW:2;
            uint32_t SWS:2;
            uint32_t HPRE:4;
            uint32_t Reserved1:2;
            uint32_t PPRE1:3;
            uint32_t PPRE2:3;
            uint32_t RTCPRE:5;
            uint32_t MCO1:2;
            uint32_t I2SSRC:1;
            uint32_t MCO1PRE:3;
            uint32_t MCO2PRE:3;
            uint32_t MCO2:2;
        }CFGR;
        uint32_t REG_CFGR;
    };
    
    union {
        struct {
            uint32_t LSIRDYF:1;
            uint32_t LSERDYF:1;
            uint32_t HSIRDYF:1;
            uint32_t HSERDYF:1;
            uint32_t PLLRDYF:1;
            uint32_t PLLI2SRDYF:1;
            uint32_t CSSF:1;
            uint32_t Reserved1:1;
            uint32_t LSIRDYIE:1;
            uint32_t LSERDYIE:1;
            uint32_t HSIRDYIE:1;
            uint32_t HSERDYIE:1;
            uint32_t PLLRDYIE:1;
            uint32_t PLLI2SRDYIE:1;
            uint32_t Reserved2:2;
            uint32_t LSIRDYC:1;
            uint32_t LSERDYC:1;
            uint32_t HSIRDYC:1;
            uint32_t HSERDYC:1;
            uint32_t PLLRDYC:1;
            uint32_t PLLI2SRDYC:1;
            uint32_t CSSC:1;
            uint32_t Reserved3:9;
        }CIR;
        uint32_t REG_CIR;
    };

    union {
        struct {
            uint32_t GPIOARST:1;
            uint32_t GPIOBRST:1;
            uint32_t GPIOCRST:1;
            uint32_t GPIODRST:1;
            uint32_t GPIOERST:1;
            uint32_t Reserved1:2;
            uint32_t GPIOHRST:1;
            uint32_t Reserved2:4;
            uint32_t CRCRST:1;
            uint32_t Reserved3:5;
            uint32_t DMA1RST:1;
            uint32_t DMA2RST:1;
            uint32_t Reserved4:13;
        }AHB1RSTR;
        uint32_t REG_AHB1RSTR;
    };

    union {
        struct {
            uint32_t Reserved1:8;
            uint32_t OTGFSRST:1;
            uint32_t Reserved2:23;
        }AHB2RSTR;
        uint32_t REG_AHB2RSTR;
    };

    const uint32_t RESERVED[2];

};


