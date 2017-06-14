/*
 * Disk.cpp
 *
 *  Created on: Nov 10, 2016
 *      Author: randy
 */

//#include "../tecmfs.raid5/Disk.h"
#include "Disk.h" // Esta linea es para corrgir la de arriba

#include "Block.h"

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>
//cout << "ESTA KA VARA "<<endl;


/**
 * Constructor.
 */
Disk::Disk() {
}

/**
 *Constructor.
 */
 Disk::Disk(string name){
	 XMLDocument doc; /*Object reader document.*/
	 //doc.LoadFile("configurationNode.xml"); /*Load the XML file.*/
	 string path = "/home/victork/Documentos/PROGRAMACION/Workspace/Raid de Prueba/DISCO 1";//doc.FirstChildElement( "diskNode" )->FirstChildElement("config")->FirstChildElement("path")->GetText();

	 const char *pathDirectory = path.c_str(); /*Get the path for the Folder.*/
	 this->pathDirectory = pathDirectory; /*Sets the path for the Folder.*/
	 this->name = name; /*Set Name.*/

	 cout <<  "Path of the Disk: " << pathDirectory << endl; /*FLAG*/

	 mkdir(pathDirectory, 0700); /*Make the Directory with the given path.*/



	 /*Create the path and the file for the Blocks to be saved.*/
	 /*A: Block A*/
	 string a = path + "/Block1.txt";
	 cout <<  "(At Disk.cpp - Disk() )Path of the Block A: " << a << endl; /*FLAG*/
	 const char *pathBlockA= a.c_str(); /*Create the path and the file for the blocks to be saved.*/
	 //char * pathBlockA= "/home/randy/DiskT/BlockA.txt";

	 /*B: Block B*/
	 string b = path + "/Block2.txt";
	 const char *pathBlockB= b.c_str();  /*Create the path and the file for the blocks to be saved.*/

	 /*C: BlockC*/
	 string c = path + "/Block3.txt";
	 const char *pathBlockC= c.c_str();  /*Create the path and the file for the blocks to be saved.*/

	 /*P: Parity*/
	 string p = path + "/Block4.txt";
	 const char *pathBlockP= p.c_str(); /*Create the path and the file for the blocks to be saved.*/

	 /*Set the blocks.*/
	 this->block1 = Block('N1', pathBlockA); /*Block A.*/
	 this->block2 = Block('N2', pathBlockB); /*Block B.*/
	 this->block3 = Block('N3', pathBlockC); /*Block C.*/
	 this->blockP = Block('P', pathBlockP); /*Block for the Parity.*/

	 /*Inserting the Blocks into the Vector.*/
	 vectorBlocks.push_back(block1);
	 vectorBlocks.push_back(block2);
	 vectorBlocks.push_back(block3);
	 vectorBlocks.push_back(blockP);
 }


/**
 * Destroyer.
 */
Disk::~Disk() {
}

/**
 * Return the path of the directory where is
 * the file saved.
 *
 * @return pathDirectory const char*
 */
const char * Disk::getPathDirectory(){
	return pathDirectory;
}

/**
 * Return the name of the Disk.
 *
 * @return name string
 */
string Disk::getName(){
	return name;
}


/**
 * Return the the vector that contains all the
 * Blocks that made up the Disk.
 *
 * @return vectorBlocks vector<Blocks>
 */
vector<Block> Disk::getVectorBlocks(){
	return vectorBlocks;
}

/**
 * Return the Block A of the Disk.
 *
 * @return blockA Block
 */
Block Disk::getBlockA(){
	return block1;
}

/**
 * Return the Block B of the Disk.
 *
 * @return blockB Block
 */
Block Disk::getBlockB(){
	return block2;
}

/**
 * Return the Block C of the Disk.
 *
 * @return blockC Block
 */
Block Disk::getBlockC(){
	return block3;
}

/**
 * Return the Block P of the Disk.
 *
 * @return blockP Block
 */
Block Disk::getBlockP(){
	return blockP;
}

/**
 * Receive data (string) and a number (int) of the block
 * to save the data.
 *
 * @param data string, i int
 */
void Disk::saveDataBlock(string data, int i){
	vectorBlocks.at(i).saveData(data);
}

/**
 * Receive the calculated parity (string) and saved
 * on the specific Block of the Disk to the parity.
 *
 * @param parity data
 */
void Disk::saveParity(string parity){
	vectorBlocks.at(3).saveData(parity);

}

/**
 *Takes from the Disk's Blocks all information
 *and keep the Blocks empty.
 *
 *@return allData string
 */
string Disk::sendDataDisk(){
	string allData, dataA, dataB, dataC;
	dataA = vectorBlocks.at(0).getData();
	dataB = vectorBlocks.at(1).getData();
	dataC = vectorBlocks.at(2).getData();
	allData = dataA + dataB + dataC;
	cout << "Disk's data sent succesfully." << endl;
	//this->cleanDisk();
	return allData;
}

/**
 * Send the parity, as a string, of the Disk, if the Disk
 * has it.
 *
 * @return parity string
 */
string Disk::sendParityDisk(){
	string parity;
	parity = vectorBlocks.at(3).getData();
	return parity;
}


/**
 * Empty of the files that makes up the Disk.
 */
void Disk::cleanDisk(){
	vectorBlocks.at(0).cleanBlock();
	vectorBlocks.at(1).cleanBlock();
	vectorBlocks.at(2).cleanBlock();
	vectorBlocks.at(3).cleanBlock();
}

/**
 * Check the size of the Disk, if it is possible
 * to save data.
 *
 * @return answer bool
 */
bool Disk::checkSize(){
	bool answer = false;
	if (this->getSizeDisk() < 40000000)
		answer= true;
	return answer;
}


/**
 *Get the size of the Disk by adding the
 *individual sizes of all the Blocks.
 *
 *@return totalSize int
 */
int Disk::getSizeDisk(){
	int totalSize;
	for(int i = 0; i<4;i++){
		totalSize += this->getVectorBlocks().at(i).getSizeData();
	}
	return totalSize;
}

/**
 * Delete an espific Block from the Disk.
 */
void Disk::deleteBlock(int i){
	vectorBlocks.at(i).deleteFile();
	vectorBlocks.at(i).~Block();
}

void Disk::leerBloque(int index){
	vectorBlocks.at(index).readData();
}
