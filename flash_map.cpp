/*
 * flash_map.cpp
 *
 *  Created on: Jul 6, 2019
 *      Author: gdbeckstein
 */

#include "DataFlashBlockDevice.h"
#include "BlockDevice.h"
// #include "QSPIFBlockDevice.h"
#include "SlicingBlockDevice.h"

DataFlashBlockDevice dfspi_bd(SPI_MOSI, SPI_MISO, SPI_SCK, SPI_CS);

// QSPIFBlockDevice qspi_bd(QSPI_FLASH1_IO0, QSPI_FLASH1_IO1, QSPI_FLASH1_IO2, QSPI_FLASH1_IO3,
// 		QSPI_FLASH1_SCK, QSPI_FLASH1_CSN, QSPIF_POLARITY_MODE_0, MBED_CONF_QSPIF_QSPI_FREQ);

SlicingBlockDevice raw_binary_bd(&dfspi_bd, 0x200000, (0x200000 + 819200));

mbed::BlockDevice* mcuboot_secondary_bd = (mbed::BlockDevice*) &raw_binary_bd;

void mbed_mcuboot_user_init(void) {
	dfspi_bd.init();
	mcuboot_secondary_bd->init();
}
