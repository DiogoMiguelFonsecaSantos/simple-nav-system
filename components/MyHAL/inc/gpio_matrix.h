/*
 * gpio_matrix.h
 *
 *  Created on: 13/04/2025
 *      Author: Diogo
 */

#ifndef COMPONENTS_MYHAL_INC_GPIO_MATRIX_H_
#define COMPONENTS_MYHAL_INC_GPIO_MATRIX_H_

#include <stdint.h>
#include <stdbool.h>

// Registradores da GPIO Matrix (Endereços absolutos)
#define GPIO_MATRIX_BASE 0x3FF44000


typedef volatile struct {
    uint32_t OUT_REG;               // 0x04 - GPIO 0-31 output
    uint32_t OUT_W1TS_REG;          // 0x08 - GPIO 0-31 bit set
    uint32_t OUT_W1TC_REG;          // 0x0C - GPIO 0-31 bit clear
    uint32_t OUT1_REG;              // 0x10 - GPIO 32-39 output
    uint32_t OUT1_W1TS_REG;         // 0x14 - GPIO 32-39 bit set
    uint32_t OUT1_W1TC_REG;         // 0x18 - GPIO 32-39 bit clear
    uint32_t ENABLE_REG;            // 0x20 - GPIO 0-31 output enable
    uint32_t ENABLE_W1TS_REG;       // 0x24 - GPIO 0-31 enable set
    uint32_t ENABLE_W1TC_REG;       // 0x28 - GPIO 0-31 enable clear
    uint32_t ENABLE1_REG;           // 0x2C - GPIO 32-39 output enable
    uint32_t ENABLE1_W1TS_REG;      // 0x30 - GPIO 32-39 enable set
    uint32_t ENABLE1_W1TC_REG;      // 0x34 - GPIO 32-39 enable clear
    uint32_t STRAP_REG;             // 0x38 - GPIO 0-31 strap
    uint32_t IN_REG;                // 0x3C - GPIO 0-31 input
    uint32_t IN1_REG;               // 0x40 - GPIO 32-39 input
    uint32_t STATUS_REG;            // 0x44 - GPIO 0-31 status
    uint32_t STATUS_W1TS_REG ;      // 0x48 - GPIO 0-31 status set
    uint32_t STATUS_W1TC_REG ;      // 0x4C - GPIO 0-31 status clear
    uint32_t STATUS1_REG;           // 0x50 - GPIO 32-39 status
    uint32_t STATUS1_W1TS_REG;      // 0x54 - GPIO 32-39 status set
    uint32_t STATUS1_W1TC_REG;      // 0x58 - GPIO 32-39 status clear
    uint32_t ACPU_INT_REG;          // 0x60 - GPIO 0-31 ACPU interrupt
    uint32_t ACPU_NMI_INT_REG;      // 0x64 - GPIO 0-31 ACPU NMI interrupt
    uint32_t PCPU_INT_REG;          // 0x68 - GPIO 0-31 PCPU interrupt
    uint32_t PCPU_NMI_INT_REG;      // 0x6C - GPIO 0-31 PCPU NMI interrupt
    uint32_t ACPU_INT1_REG;         // 0x74 - GPIO 32-39 ACPU interrupt
    uint32_t ACPU_NMI_INT1_REG;     // 0x78 - GPIO 32-39 ACPU NMI interrupt
    uint32_t PCPU_INT1_REG;         // 0x7C - GPIO 32-39 PCPU interrupt
    uint32_t PCPU_NMI_INT1_REG;     // 0x80 - GPIO 32-39 PCPU NMI interrupt
    uint32_t PIN0_REG;              // 0x88 - GPIO 0 pin
    uint32_t PIN1_REG;              // 0x8C - GPIO 1 pin
    uint32_t PIN2_REG;              // 0x90 - GPIO 2 pin
    uint32_t PIN3_REG;              // 0x94 - GPIO 3 pin
    uint32_t PIN4_REG;              // 0x98 - GPIO 4 pin
    uint32_t PIN5_REG;              // 0x9C - GPIO 5 pin
    uint32_t PIN6_REG;              // 0xA0 - GPIO 6 pin
    uint32_t PIN7_REG;              // 0xA4 - GPIO 7 pin
    uint32_t PIN8_REG;              // 0xA8 - GPIO 8 pin
    uint32_t PIN9_REG;              // 0xAC - GPIO 9 pin
    uint32_t PIN10_REG;             // 0xB0 - GPIO 10 pin
    uint32_t PIN11_REG;             // 0xB4 - GPIO 11 pin
    uint32_t PIN12_REG;             // 0xB8 - GPIO 12 pin
    uint32_t PIN13_REG;             // 0xBC - GPIO 13 pin
    uint32_t PIN14_REG;             // 0xC0 - GPIO 14 pin
    uint32_t PIN15_REG;             // 0xC4 - GPIO 15 pin
    uint32_t PIN16_REG;             // 0xC8 - GPIO 16 pin
    uint32_t PIN17_REG;             // 0xCC - GPIO 17 pin
    uint32_t PIN18_REG;             // 0xD0 - GPIO 18 pin
    uint32_t PIN19_REG;             // 0xD4 - GPIO 19 pin
    uint32_t PIN20_REG;             // 0xD8 - GPIO 20 pin
    uint32_t PIN21_REG;             // 0xDC - GPIO 21 pin
    uint32_t PIN22_REG;             // 0xE0 - GPIO 22 pin
    uint32_t PIN23_REG;             // 0xE4 - GPIO 23 pin
    uint32_t PIN24_REG;             // 0xE8 - GPIO 24 pin
    uint32_t PIN25_REG;             // 0xEC - GPIO 25 pin
    uint32_t PIN26_REG;             // 0xF0 - GPIO 26 pin
    uint32_t PIN27_REG;             // 0xF4 - GPIO 27 pin
    uint32_t PIN28_REG;             // 0xF8 - GPIO 28 pin
    uint32_t PIN29_REG;             // 0xFC - GPIO 29 pin
    uint32_t PIN30_REG;             // 0x100 - GPIO 30 pin
    uint32_t PIN31_REG;             // 0x104 - GPIO 31 pin
    uint32_t PIN32_REG;             // 0x108 - GPIO 32 pin
    uint32_t PIN33_REG;             // 0x10C - GPIO 33 pin
    uint32_t PIN34_REG;             // 0x110 - GPIO 34 pin
    uint32_t PIN35_REG;             // 0x114 - GPIO 35 pin
    uint32_t PIN36_REG;             // 0x118 - GPIO 36 pin
    uint32_t PIN37_REG;             // 0x11C - GPIO 37 pin
    uint32_t PIN38_REG;             // 0x120 - GPIO 38 pin
    uint32_t PIN39_REG;             // 0x124 - GPIO 39 pin
    uint32_t GPIO_FUNC0_IN_SEL_CFG; // 0x130 - GPIO 0 function select
    uint32_t GPIO_FUNC1_IN_SEL_CFG; // 0x134 - GPIO 1 function select
    uint32_t GPIO_FUNC2_IN_SEL_CFG; // 0x138 - GPIO 2 function select
    uint32_t GPIO_FUNC3_IN_SEL_CFG; // 0x13C - GPIO 3 function select
    uint32_t GPIO_FUNC4_IN_SEL_CFG; // 0x140 - GPIO 4 function select
    uint32_t GPIO_FUNC5_IN_SEL_CFG; // 0x144 - GPIO 5 function select
    uint32_t GPIO_FUNC6_IN_SEL_CFG; // 0x148 - GPIO 6 function select
    uint32_t GPIO_FUNC7_IN_SEL_CFG; // 0x14C - GPIO 7 function select
    uint32_t GPIO_FUNC8_IN_SEL_CFG; // 0x150 - GPIO 8 function select
    uint32_t GPIO_FUNC9_IN_SEL_CFG; // 0x154 - GPIO 9 function select
    uint32_t GPIO_FUNC10_IN_SEL_CFG; // 0x158 - GPIO 10 function select
    uint32_t GPIO_FUNC11_IN_SEL_CFG; // 0x15C - GPIO 11 function select
    uint32_t GPIO_FUNC12_IN_SEL_CFG; // 0x160 - GPIO 12 function select
    uint32_t GPIO_FUNC13_IN_SEL_CFG; // 0x164 - GPIO 13 function select
    uint32_t GPIO_FUNC14_IN_SEL_CFG; // 0x168 - GPIO 14 function select
    uint32_t GPIO_FUNC15_IN_SEL_CFG; // 0x16C - GPIO 15 function select
    uint32_t GPIO_FUNC16_IN_SEL_CFG; // 0x170 - GPIO 16 function select
    uint32_t GPIO_FUNC17_IN_SEL_CFG; // 0x174 - GPIO 17 function select
    uint32_t GPIO_FUNC18_IN_SEL_CFG; // 0x178 - GPIO 18 function select
    uint32_t GPIO_FUNC19_IN_SEL_CFG; // 0x17C - GPIO 19 function select
    uint32_t GPIO_FUNC20_IN_SEL_CFG; // 0x180 - GPIO 20 function select
    uint32_t GPIO_FUNC21_IN_SEL_CFG; // 0x184 - GPIO 21 function select
    uint32_t GPIO_FUNC22_IN_SEL_CFG; // 0x188 - GPIO 22 function select
    uint32_t GPIO_FUNC23_IN_SEL_CFG; // 0x18C - GPIO 23 function select
    uint32_t GPIO_FUNC24_IN_SEL_CFG; // 0x190 - GPIO 24 function select
    uint32_t GPIO_FUNC25_IN_SEL_CFG; // 0x194 - GPIO 25 function select
    uint32_t GPIO_FUNC26_IN_SEL_CFG; // 0x198 - GPIO 26 function select
    uint32_t GPIO_FUNC27_IN_SEL_CFG; // 0x19C - GPIO 27 function select
    uint32_t GPIO_FUNC28_IN_SEL_CFG; // 0x1A0 - GPIO 28 function select
    uint32_t GPIO_FUNC29_IN_SEL_CFG; // 0x1A4 - GPIO 29 function select
    uint32_t GPIO_FUNC30_IN_SEL_CFG; // 0x1A8 - GPIO 30 function select
    uint32_t GPIO_FUNC31_IN_SEL_CFG; // 0x1AC - GPIO 31 function select
    uint32_t GPIO_FUNC32_IN_SEL_CFG; // 0x1B0 - GPIO 32 function select
    uint32_t GPIO_FUNC33_IN_SEL_CFG; // 0x1B4 - GPIO 33 function select
    uint32_t GPIO_FUNC34_IN_SEL_CFG; // 0x1B8 - GPIO 34 function select
    uint32_t GPIO_FUNC35_IN_SEL_CFG; // 0x1BC - GPIO 35 function select
    uint32_t GPIO_FUNC36_IN_SEL_CFG; // 0x1C0 - GPIO 36 function select
    uint32_t GPIO_FUNC37_IN_SEL_CFG; // 0x1C4 - GPIO 37 function select
    uint32_t GPIO_FUNC38_IN_SEL_CFG; // 0x1C8 - GPIO 38 function select
    uint32_t GPIO_FUNC39_IN_SEL_CFG; // 0x1CC - GPIO 39 function select
    uint32_t GPIO_FUNC40_IN_SEL_CFG; // 0x1D0 - GPIO 40 function select
    uint32_t GPIO_FUNC41_IN_SEL_CFG; // 0x1D4 - GPIO 41 function select
    uint32_t GPIO_FUNC42_IN_SEL_CFG; // 0x1D8 - GPIO 42 function select
    uint32_t GPIO_FUNC43_IN_SEL_CFG; // 0x1DC - GPIO 43 function select
    uint32_t GPIO_FUNC44_IN_SEL_CFG; // 0x1E0 - GPIO 44 function select
    uint32_t GPIO_FUNC45_IN_SEL_CFG; // 0x1E4 - GPIO 45 function select
    uint32_t GPIO_FUNC46_IN_SEL_CFG; // 0x1E8 - GPIO 46 function select
    uint32_t GPIO_FUNC47_IN_SEL_CFG; // 0x1EC - GPIO 47 function select
    uint32_t GPIO_FUNC48_IN_SEL_CFG; // 0x1F0 - GPIO 48 function select
    uint32_t GPIO_FUNC49_IN_SEL_CFG; // 0x1F4 - GPIO 49 function select
    uint32_t GPIO_FUNC50_IN_SEL_CFG; // 0x1F8 - GPIO 50 function select
    uint32_t GPIO_FUNC51_IN_SEL_CFG; // 0x1FC - GPIO 51 function select
    uint32_t GPIO_FUNC52_IN_SEL_CFG; // 0x200 - GPIO 52 function select
    uint32_t GPIO_FUNC53_IN_SEL_CFG; // 0x204 - GPIO 53 function select
    uint32_t GPIO_FUNC54_IN_SEL_CFG; // 0x208 - GPIO 54 function select
    uint32_t GPIO_FUNC55_IN_SEL_CFG; // 0x20C - GPIO 55 function select
    uint32_t GPIO_FUNC56_IN_SEL_CFG; // 0x210 - GPIO 56 function select
    uint32_t GPIO_FUNC57_IN_SEL_CFG; // 0x214 - GPIO 57 function select
    uint32_t GPIO_FUNC58_IN_SEL_CFG; // 0x218 - GPIO 58 function select
    uint32_t GPIO_FUNC59_IN_SEL_CFG; // 0x21C - GPIO 59 function select
    uint32_t GPIO_FUNC60_IN_SEL_CFG; // 0x220 - GPIO 60 function select
    uint32_t GPIO_FUNC61_IN_SEL_CFG; // 0x224 - GPIO 61 function select
    uint32_t GPIO_FUNC62_IN_SEL_CFG; // 0x228 - GPIO 62 function select
    uint32_t GPIO_FUNC63_IN_SEL_CFG; // 0x22C - GPIO 63 function select
    uint32_t GPIO_FUNC64_IN_SEL_CFG; // 0x230 - GPIO 64 function select
    uint32_t GPIO_FUNC65_IN_SEL_CFG; // 0x234 - GPIO 65 function select
    uint32_t GPIO_FUNC66_IN_SEL_CFG; // 0x238 - GPIO 66 function select
    uint32_t GPIO_FUNC67_IN_SEL_CFG; // 0x23C - GPIO 67 function select
    uint32_t GPIO_FUNC68_IN_SEL_CFG; // 0x240 - GPIO 68 function select
    uint32_t GPIO_FUNC69_IN_SEL_CFG; // 0x244 - GPIO 69 function select
    uint32_t GPIO_FUNC70_IN_SEL_CFG; // 0x248 - GPIO 70 function select
    uint32_t GPIO_FUNC71_IN_SEL_CFG; // 0x24C - GPIO 71 function select
    uint32_t GPIO_FUNC72_IN_SEL_CFG; // 0x250 - GPIO 72 function select
    uint32_t GPIO_FUNC73_IN_SEL_CFG; // 0x254 - GPIO 73 function select
    uint32_t GPIO_FUNC74_IN_SEL_CFG; // 0x258 - GPIO 74 function select
    uint32_t GPIO_FUNC75_IN_SEL_CFG; // 0x25C - GPIO 75 function select
    uint32_t GPIO_FUNC76_IN_SEL_CFG; // 0x260 - GPIO 76 function select
    uint32_t GPIO_FUNC77_IN_SEL_CFG; // 0x264 - GPIO 77 function select
    uint32_t GPIO_FUNC78_IN_SEL_CFG; // 0x268 - GPIO 78 function select
    uint32_t GPIO_FUNC79_IN_SEL_CFG; // 0x26C - GPIO 79 function select
    uint32_t GPIO_FUNC80_IN_SEL_CFG; // 0x270 - GPIO 80 function select
    uint32_t GPIO_FUNC81_IN_SEL_CFG; // 0x274 - GPIO 81 function select
    uint32_t GPIO_FUNC82_IN_SEL_CFG; // 0x278 - GPIO 82 function select
    uint32_t GPIO_FUNC83_IN_SEL_CFG; // 0x27C - GPIO 83 function select
    uint32_t GPIO_FUNC84_IN_SEL_CFG; // 0x280 - GPIO 84 function select
    uint32_t GPIO_FUNC85_IN_SEL_CFG; // 0x284 - GPIO 85 function select
    uint32_t GPIO_FUNC86_IN_SEL_CFG; // 0x288 - GPIO 86 function select
    uint32_t GPIO_FUNC87_IN_SEL_CFG; // 0x28C - GPIO 87 function select
    uint32_t GPIO_FUNC88_IN_SEL_CFG; // 0x290 - GPIO 88 function select
    uint32_t GPIO_FUNC89_IN_SEL_CFG; // 0x294 - GPIO 89 function select
    uint32_t GPIO_FUNC90_IN_SEL_CFG; // 0x298 - GPIO 90 function select
    uint32_t GPIO_FUNC91_IN_SEL_CFG; // 0x29C - GPIO 91 function select
    uint32_t GPIO_FUNC92_IN_SEL_CFG; // 0x2A0 - GPIO 92 function select
    uint32_t GPIO_FUNC93_IN_SEL_CFG; // 0x2A4 - GPIO 93 function select
    uint32_t GPIO_FUNC94_IN_SEL_CFG; // 0x2A8 - GPIO 94 function select
    uint32_t GPIO_FUNC95_IN_SEL_CFG; // 0x2AC - GPIO 95 function select
    uint32_t GPIO_FUNC96_IN_SEL_CFG; // 0x2B0 - GPIO 96 function select
    uint32_t GPIO_FUNC97_IN_SEL_CFG; // 0x2B4 - GPIO 97 function select
    uint32_t GPIO_FUNC98_IN_SEL_CFG; // 0x2B8 - GPIO 98 function select
    uint32_t GPIO_FUNC99_IN_SEL_CFG; // 0x2BC - GPIO 99 function select
    uint32_t GPIO_FUNC100_IN_SEL_CFG; // 0x2C0 - GPIO 100 function select
    uint32_t GPIO_FUNC101_IN_SEL_CFG; // 0x2C4 - GPIO 101 function select
    uint32_t GPIO_FUNC102_IN_SEL_CFG; // 0x2C8 - GPIO 102 function select
    uint32_t GPIO_FUNC103_IN_SEL_CFG; // 0x2CC - GPIO 103 function select
    uint32_t GPIO_FUNC104_IN_SEL_CFG; // 0x2D0 - GPIO 104 function select
    uint32_t GPIO_FUNC105_IN_SEL_CFG; // 0x2D4 - GPIO 105 function select
    uint32_t GPIO_FUNC106_IN_SEL_CFG; // 0x2D8 - GPIO 106 function select
    uint32_t GPIO_FUNC107_IN_SEL_CFG; // 0x2DC - GPIO 107 function select
    uint32_t GPIO_FUNC108_IN_SEL_CFG; // 0x2E0 - GPIO 108 function select
    uint32_t GPIO_FUNC109_IN_SEL_CFG; // 0x2E4 - GPIO 109 function select
    uint32_t GPIO_FUNC110_IN_SEL_CFG; // 0x2E8 - GPIO 110 function select
    uint32_t GPIO_FUNC111_IN_SEL_CFG; // 0x2EC - GPIO 111 function select
    uint32_t GPIO_FUNC112_IN_SEL_CFG; // 0x2F0 - GPIO 112 function select
    uint32_t GPIO_FUNC113_IN_SEL_CFG; // 0x2F4 - GPIO 113 function select
    uint32_t GPIO_FUNC114_IN_SEL_CFG; // 0x2F8 - GPIO 114 function select
    uint32_t GPIO_FUNC115_IN_SEL_CFG; // 0x2FC - GPIO 115 function select
    uint32_t GPIO_FUNC116_IN_SEL_CFG; // 0x300 - GPIO 116 function select
    uint32_t GPIO_FUNC117_IN_SEL_CFG; // 0x304 - GPIO 117 function select
    uint32_t GPIO_FUNC118_IN_SEL_CFG; // 0x308 - GPIO 118 function select
    uint32_t GPIO_FUNC119_IN_SEL_CFG; // 0x30C - GPIO 119 function select
    uint32_t GPIO_FUNC120_IN_SEL_CFG; // 0x310 - GPIO 120 function select
    uint32_t GPIO_FUNC121_IN_SEL_CFG; // 0x314 - GPIO 121 function select
    uint32_t GPIO_FUNC122_IN_SEL_CFG; // 0x318 - GPIO 122 function select
    uint32_t GPIO_FUNC123_IN_SEL_CFG; // 0x31C - GPIO 123 function select
    uint32_t GPIO_FUNC124_IN_SEL_CFG; // 0x320 - GPIO 124 function select
    uint32_t GPIO_FUNC125_IN_SEL_CFG; // 0x324 - GPIO 125 function select
    uint32_t GPIO_FUNC126_IN_SEL_CFG; // 0x328 - GPIO 126 function select
    uint32_t GPIO_FUNC127_IN_SEL_CFG; // 0x32C - GPIO 127 function select
    uint32_t GPIO_FUNC128_IN_SEL_CFG; // 0x330 - GPIO 128 function select
    uint32_t GPIO_FUNC129_IN_SEL_CFG; // 0x334 - GPIO 129 function select
    uint32_t GPIO_FUNC130_IN_SEL_CFG; // 0x338 - GPIO 130 function select
    uint32_t GPIO_FUNC131_IN_SEL_CFG; // 0x33C - GPIO 131 function select
    uint32_t GPIO_FUNC132_IN_SEL_CFG; // 0x340 - GPIO 132 function select
    uint32_t GPIO_FUNC133_IN_SEL_CFG; // 0x344 - GPIO 133 function select
    uint32_t GPIO_FUNC134_IN_SEL_CFG; // 0x348 - GPIO 134 function select
    uint32_t GPIO_FUNC135_IN_SEL_CFG; // 0x34C - GPIO 135 function select
    uint32_t GPIO_FUNC136_IN_SEL_CFG; // 0x350 - GPIO 136 function select
    uint32_t GPIO_FUNC137_IN_SEL_CFG; // 0x354 - GPIO 137 function select
    uint32_t GPIO_FUNC138_IN_SEL_CFG; // 0x358 - GPIO 138 function select
    uint32_t GPIO_FUNC139_IN_SEL_CFG; // 0x35C - GPIO 139 function select
    uint32_t GPIO_FUNC140_IN_SEL_CFG; // 0x360 - GPIO 140 function select
    uint32_t GPIO_FUNC141_IN_SEL_CFG; // 0x364 - GPIO 141 function select
    uint32_t GPIO_FUNC142_IN_SEL_CFG; // 0x368 - GPIO 142 function select
    uint32_t GPIO_FUNC143_IN_SEL_CFG; // 0x36C - GPIO 143 function select
    uint32_t GPIO_FUNC144_IN_SEL_CFG; // 0x370 - GPIO 144 function select
    uint32_t GPIO_FUNC145_IN_SEL_CFG; // 0x374 - GPIO 145 function select
    uint32_t GPIO_FUNC146_IN_SEL_CFG; // 0x378 - GPIO 146 function select
    uint32_t GPIO_FUNC147_IN_SEL_CFG; // 0x37C - GPIO 147 function select
    uint32_t GPIO_FUNC148_IN_SEL_CFG; // 0x380 - GPIO 148 function select
    uint32_t GPIO_FUNC149_IN_SEL_CFG; // 0x384 - GPIO 149 function select
    uint32_t GPIO_FUNC150_IN_SEL_CFG; // 0x388 - GPIO 150 function select
    uint32_t GPIO_FUNC151_IN_SEL_CFG; // 0x38C - GPIO 151 function select
    uint32_t GPIO_FUNC152_IN_SEL_CFG; // 0x390 - GPIO 152 function select
    uint32_t GPIO_FUNC153_IN_SEL_CFG; // 0x394 - GPIO 153 function select
    uint32_t GPIO_FUNC154_IN_SEL_CFG; // 0x398 - GPIO 154 function select
    uint32_t GPIO_FUNC155_IN_SEL_CFG; // 0x39C - GPIO 155 function select
    uint32_t GPIO_FUNC156_IN_SEL_CFG; // 0x3A0 - GPIO 156 function select
    uint32_t GPIO_FUNC157_IN_SEL_CFG; // 0x3A4 - GPIO 157 function select
    uint32_t GPIO_FUNC158_IN_SEL_CFG; // 0x3A8 - GPIO 158 function select
    uint32_t GPIO_FUNC159_IN_SEL_CFG; // 0x3AC - GPIO 159 function select
    uint32_t GPIO_FUNC160_IN_SEL_CFG; // 0x3B0 - GPIO 160 function select
    uint32_t GPIO_FUNC161_IN_SEL_CFG; // 0x3B4 - GPIO 161 function select
    uint32_t GPIO_FUNC162_IN_SEL_CFG; // 0x3B8 - GPIO 162 function select
    uint32_t GPIO_FUNC163_IN_SEL_CFG; // 0x3BC - GPIO 163 function select
    uint32_t GPIO_FUNC164_IN_SEL_CFG; // 0x3C0 - GPIO 164 function select
    uint32_t GPIO_FUNC165_IN_SEL_CFG; // 0x3C4 - GPIO 165 function select
    uint32_t GPIO_FUNC166_IN_SEL_CFG; // 0x3C8 - GPIO 166 function select
    uint32_t GPIO_FUNC167_IN_SEL_CFG; // 0x3CC - GPIO 167 function select
    uint32_t GPIO_FUNC168_IN_SEL_CFG; // 0x3D0 - GPIO 168 function select
    uint32_t GPIO_FUNC169_IN_SEL_CFG; // 0x3D4 - GPIO 169 function select
    uint32_t GPIO_FUNC170_IN_SEL_CFG; // 0x3D8 - GPIO 170 function select
    uint32_t GPIO_FUNC171_IN_SEL_CFG; // 0x3DC - GPIO 171 function select
    uint32_t GPIO_FUNC172_IN_SEL_CFG; // 0x3E0 - GPIO 172 function select
    uint32_t GPIO_FUNC173_IN_SEL_CFG; // 0x3E4 - GPIO 173 function select
    uint32_t GPIO_FUNC174_IN_SEL_CFG; // 0x3E8 - GPIO 174 function select
    uint32_t GPIO_FUNC175_IN_SEL_CFG; // 0x3EC - GPIO 175 function select
    uint32_t GPIO_FUNC176_IN_SEL_CFG; // 0x3F0 - GPIO 176 function select
    uint32_t GPIO_FUNC177_IN_SEL_CFG; // 0x3F4 - GPIO 177 function select
    uint32_t GPIO_FUNC178_IN_SEL_CFG; // 0x3F8 - GPIO 178 function select
    uint32_t GPIO_FUNC179_IN_SEL_CFG; // 0x3FC - GPIO 179 function select
    uint32_t GPIO_FUNC180_IN_SEL_CFG; // 0x400 - GPIO 180 function select
    uint32_t GPIO_FUNC181_IN_SEL_CFG; // 0x404 - GPIO 181 function select
    uint32_t GPIO_FUNC182_IN_SEL_CFG; // 0x408 - GPIO 182 function select
    uint32_t GPIO_FUNC183_IN_SEL_CFG; // 0x40C - GPIO 183 function select
    uint32_t GPIO_FUNC184_IN_SEL_CFG; // 0x410 - GPIO 184 function select
    uint32_t GPIO_FUNC185_IN_SEL_CFG; // 0x414 - GPIO 185 function select
    uint32_t GPIO_FUNC186_IN_SEL_CFG; // 0x418 - GPIO 186 function select
    uint32_t GPIO_FUNC187_IN_SEL_CFG; // 0x41C - GPIO 187 function select
    uint32_t GPIO_FUNC188_IN_SEL_CFG; // 0x420 - GPIO 188 function select
    uint32_t GPIO_FUNC189_IN_SEL_CFG; // 0x424 - GPIO 189 function select
    uint32_t GPIO_FUNC190_IN_SEL_CFG; // 0x428 - GPIO 190 function select
    uint32_t GPIO_FUNC191_IN_SEL_CFG; // 0x42C - GPIO 191 function select
    uint32_t GPIO_FUNC192_IN_SEL_CFG; // 0x430 - GPIO 192 function select
    uint32_t GPIO_FUNC193_IN_SEL_CFG; // 0x434 - GPIO 193 function select
    uint32_t GPIO_FUNC194_IN_SEL_CFG; // 0x438 - GPIO 194 function select
    uint32_t GPIO_FUNC195_IN_SEL_CFG; // 0x43C - GPIO 195 function select
    uint32_t GPIO_FUNC196_IN_SEL_CFG; // 0x440 - GPIO 196 function select
    uint32_t GPIO_FUNC197_IN_SEL_CFG; // 0x444 - GPIO 197 function select
    uint32_t GPIO_FUNC198_IN_SEL_CFG; // 0x448 - GPIO 198 function select
    uint32_t GPIO_FUNC199_IN_SEL_CFG; // 0x44C - GPIO 199 function select
    uint32_t GPIO_FUNC200_IN_SEL_CFG; // 0x450 - GPIO 200 function select
    uint32_t GPIO_FUNC201_IN_SEL_CFG; // 0x454 - GPIO 201 function select
    uint32_t GPIO_FUNC202_IN_SEL_CFG; // 0x458 - GPIO 202 function select
    uint32_t GPIO_FUNC203_IN_SEL_CFG; // 0x45C - GPIO 203 function select
    uint32_t GPIO_FUNC204_IN_SEL_CFG; // 0x460 - GPIO 204 function select
    uint32_t GPIO_FUNC205_IN_SEL_CFG; // 0x464 - GPIO 205 function select
    uint32_t GPIO_FUNC206_IN_SEL_CFG; // 0x468 - GPIO 206 function select
    uint32_t GPIO_FUNC207_IN_SEL_CFG; // 0x46C - GPIO 207 function select
    uint32_t GPIO_FUNC208_IN_SEL_CFG; // 0x470 - GPIO 208 function select
    uint32_t GPIO_FUNC209_IN_SEL_CFG; // 0x474 - GPIO 209 function select
    uint32_t GPIO_FUNC210_IN_SEL_CFG; // 0x478 - GPIO 210 function select
    uint32_t GPIO_FUNC211_IN_SEL_CFG; // 0x47C - GPIO 211 function select
    uint32_t GPIO_FUNC212_IN_SEL_CFG; // 0x480 - GPIO 212 function select
    uint32_t GPIO_FUNC213_IN_SEL_CFG; // 0x484 - GPIO 213 function select
    uint32_t GPIO_FUNC214_IN_SEL_CFG; // 0x488 - GPIO 214 function select
    uint32_t GPIO_FUNC215_IN_SEL_CFG; // 0x48C - GPIO 215 function select
    uint32_t GPIO_FUNC216_IN_SEL_CFG; // 0x490 - GPIO 216 function select
    uint32_t GPIO_FUNC217_IN_SEL_CFG; // 0x494 - GPIO 217 function select
    uint32_t GPIO_FUNC218_IN_SEL_CFG; // 0x498 - GPIO 218 function select
    uint32_t GPIO_FUNC219_IN_SEL_CFG; // 0x49C - GPIO 219 function select
    uint32_t GPIO_FUNC220_IN_SEL_CFG; // 0x4A0 - GPIO 220 function select
    uint32_t GPIO_FUNC221_IN_SEL_CFG; // 0x4A4 - GPIO 221 function select
    uint32_t GPIO_FUNC222_IN_SEL_CFG; // 0x4A8 - GPIO 222 function select
    uint32_t GPIO_FUNC223_IN_SEL_CFG; // 0x4AC - GPIO 223 function select
    uint32_t GPIO_FUNC224_IN_SEL_CFG; // 0x4B0 - GPIO 224 function select
    uint32_t GPIO_FUNC225_IN_SEL_CFG; // 0x4B4 - GPIO 225 function select
    uint32_t GPIO_FUNC226_IN_SEL_CFG; // 0x4B8 - GPIO 226 function select
    uint32_t GPIO_FUNC227_IN_SEL_CFG; // 0x4BC - GPIO 227 function select
    uint32_t GPIO_FUNC228_IN_SEL_CFG; // 0x4C0 - GPIO 228 function select
    uint32_t GPIO_FUNC229_IN_SEL_CFG; // 0x4C4 - GPIO 229 function select
    uint32_t GPIO_FUNC230_IN_SEL_CFG; // 0x4C8 - GPIO 230 function select
    uint32_t GPIO_FUNC231_IN_SEL_CFG; // 0x4CC - GPIO 231 function select
    uint32_t GPIO_FUNC232_IN_SEL_CFG; // 0x4D0 - GPIO 232 function select
    uint32_t GPIO_FUNC233_IN_SEL_CFG; // 0x4D4 - GPIO 233 function select
    uint32_t GPIO_FUNC234_IN_SEL_CFG; // 0x4D8 - GPIO 234 function select
    uint32_t GPIO_FUNC235_IN_SEL_CFG; // 0x4DC - GPIO 235 function select   
    uint32_t GPIO_FUNC236_IN_SEL_CFG; // 0x4E0 - GPIO 236 function select
    uint32_t GPIO_FUNC237_IN_SEL_CFG; // 0x4E4 - GPIO 237 function select
    uint32_t GPIO_FUNC238_IN_SEL_CFG; // 0x4E8 - GPIO 238 function select
    uint32_t GPIO_FUNC239_IN_SEL_CFG; // 0x4EC - GPIO 239 function select
    uint32_t GPIO_FUNC240_IN_SEL_CFG; // 0x4F0 - GPIO 240 function select
    uint32_t GPIO_FUNC241_IN_SEL_CFG; // 0x4F4 - GPIO 241 function select
    uint32_t GPIO_FUNC242_IN_SEL_CFG; // 0x4F8 - GPIO 242 function select
    uint32_t GPIO_FUNC243_IN_SEL_CFG; // 0x4FC - GPIO 243 function select
    uint32_t GPIO_FUNC244_IN_SEL_CFG; // 0x500 - GPIO 244 function select
    uint32_t GPIO_FUNC245_IN_SEL_CFG; // 0x504 - GPIO 245 function select
    uint32_t GPIO_FUNC246_IN_SEL_CFG; // 0x508 - GPIO 246 function select
    uint32_t GPIO_FUNC247_IN_SEL_CFG; // 0x50C - GPIO 247 function select
    uint32_t GPIO_FUNC248_IN_SEL_CFG; // 0x510 - GPIO 248 function select
    uint32_t GPIO_FUNC249_IN_SEL_CFG; // 0x514 - GPIO 249 function select
    uint32_t GPIO_FUNC250_IN_SEL_CFG; // 0x518 - GPIO 250 function select
    uint32_t GPIO_FUNC251_IN_SEL_CFG; // 0x51C - GPIO 251 function select
    uint32_t GPIO_FUNC252_IN_SEL_CFG; // 0x520 - GPIO 252 function select
    uint32_t GPIO_FUNC253_IN_SEL_CFG; // 0x524 - GPIO 253 function select
    uint32_t GPIO_FUNC254_IN_SEL_CFG; // 0x528 - GPIO 254 function select
    uint32_t GPIO_FUNC255_IN_SEL_CFG; // 0x52C - GPIO 255 function select
    uint32_t GPIO_FUNC0_OUT_SEL_CFG;  // 0x530 - GPIO 0 function select
    uint32_t GPIO_FUNC1_OUT_SEL_CFG;  // 0x534 - GPIO 1 function select
    uint32_t GPIO_FUNC2_OUT_SEL_CFG;  // 0x538 - GPIO 2 function select
    uint32_t GPIO_FUNC3_OUT_SEL_CFG;  // 0x53C - GPIO 3 function select
    uint32_t GPIO_FUNC4_OUT_SEL_CFG;  // 0x540 - GPIO 4 function select
    uint32_t GPIO_FUNC5_OUT_SEL_CFG;  // 0x544 - GPIO 5 function select
    uint32_t GPIO_FUNC6_OUT_SEL_CFG;  // 0x548 - GPIO 6 function select
    uint32_t GPIO_FUNC7_OUT_SEL_CFG;  // 0x54C - GPIO 7 function select
    uint32_t GPIO_FUNC8_OUT_SEL_CFG;  // 0x550 - GPIO 8 function select
    uint32_t GPIO_FUNC9_OUT_SEL_CFG;  // 0x554 - GPIO 9 function select
    uint32_t GPIO_FUNC10_OUT_SEL_CFG; // 0x558 - GPIO 10 function select
    uint32_t GPIO_FUNC11_OUT_SEL_CFG; // 0x55C - GPIO 11 function select
    uint32_t GPIO_FUNC12_OUT_SEL_CFG; // 0x560 - GPIO 12 function select
    uint32_t GPIO_FUNC13_OUT_SEL_CFG; // 0x564 - GPIO 13 function select
    uint32_t GPIO_FUNC14_OUT_SEL_CFG; // 0x568 - GPIO 14 function select
    uint32_t GPIO_FUNC15_OUT_SEL_CFG; // 0x56C - GPIO 15 function select
    uint32_t GPIO_FUNC16_OUT_SEL_CFG; // 0x570 - GPIO 16 function select
    uint32_t GPIO_FUNC17_OUT_SEL_CFG; // 0x574 - GPIO 17 function select
    uint32_t GPIO_FUNC18_OUT_SEL_CFG; // 0x578 - GPIO 18 function select
    uint32_t GPIO_FUNC19_OUT_SEL_CFG; // 0x57C - GPIO 19 function select
    uint32_t GPIO_FUNC21_OUT_SEL_CFG; // 0x584 - GPIO 21 function select
    uint32_t GPIO_FUNC22_OUT_SEL_CFG; // 0x588 - GPIO 22 function select
    uint32_t GPIO_FUNC23_OUT_SEL_CFG; // 0x58C - GPIO 23 function select
    uint32_t GPIO_FUNC25_OUT_SEL_CFG; // 0x594 - GPIO 25 function select
    uint32_t GPIO_FUNC26_OUT_SEL_CFG; // 0x598 - GPIO 26 function select
    uint32_t GPIO_FUNC27_OUT_SEL_CFG; // 0x59C - GPIO 27 function select
    uint32_t GPIO_FUNC32_OUT_SEL_CFG; // 0x5B0 - GPIO 32 function select
    uint32_t GPIO_FUNC33_OUT_SEL_CFG; // 0x5B4 - GPIO 33 function select
} GPIO_Matrix_Type;

#define GPIO_MATRIX ((GPIO_Matrix_Type*)GPIO_MATRIX_BASE)

// Funções de manipulação atômica
void GPIO_SetOutput(uint8_t gpio);
void GPIO_ClearOutput(uint8_t gpio);
void GPIO_EnableOutput(uint8_t gpio);
void GPIO_DisableOutput(uint8_t gpio);
bool GPIO_ReadInput(uint8_t gpio);

#endif /* COMPONENTS_MYHAL_INC_GPIO_MATRIX_H_ */
