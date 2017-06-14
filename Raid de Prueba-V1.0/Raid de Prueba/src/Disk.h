/*
 * Disk.h
 *
 *  Created on: Nov 10, 2016
 *      Author: randy
 */

#ifndef TECMFS_RAID5_DISK_H_
#define TECMFS_RAID5_DISK_H_

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

#include "Block.h"
#include "tinyxml2.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace tinyxml2;
using namespace std;

/**
 *Disk class object represent the entire Disk Node from the RAID
 *5 Architecture. It's represensation is directory, where all the
 *Block files are stored. ALl the data saved to the files is managed
 *by the Disk.
 */
class Disk {

private:
	/*Attributes*/
	const char * pathDirectory; /*Path of the location of the save data.*/
	string name; /*Name of the Disk.*/
	int size = 40000000; /*Size of the Disk.*/

	//XMLDocument doc; /*Instance for reading the xml file.*/

	vector<Block> vectorBlocks;/*Vector full of the Blocks of the Disk.*/

	Block block1; /*First or Block A of the Disk.*/
	Block block2; /*Second or Block B of the Disk.*/
	Block block3; /*Third or Block C of the Disk.*/
	Block blockP; /*Fourth or Block P (Parity) of the Disk.*/



public:
	/*Methods*/
	Disk(); /*Constructor.*/
	Disk(string name); /*+++++++++++++.*/
	virtual ~Disk(); /*Destroyer.*/

	/*Getters*/
	const char * getPathDirectory();
	string getName();
	vector<Block> getVectorBlocks();

	Block getBlockA();
	Block getBlockB();
	Block getBlockC();
	Block getBlockP();

	/*Functions of the disk.*/
	void readXMLConfig(); /*Reads the XML for the IP and the path for the Disk.*/
	void saveDataBlock(string data, int i); /*Save the data into the Block.*/
	void saveParity(string parity); /*Sava the parity.*/
	string sendDataDisk(); /*Send the data that has in the Disk.*/
	string sendParityDisk(); /*Send the parity from the Disk*/
	void cleanDisk(); /*Erase all data from blocks.*/
	bool checkSize(); /*Check if there is free space in the disk. (Checks all Blocks)*/
	int getSizeDisk(); /*Returns the actual size of the Disk by adding the data from all the Blocks.*/
	void deleteBlock(int i); /*Delete the desire Block with all information related to it.*/
	void deleteDisc(); /*Delete this Disk with all information related to it.*/
	void leerBloque(int index);

};

#endif /* TECMFS_RAID5_DISK_H_ */
