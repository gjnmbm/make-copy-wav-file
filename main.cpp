#include <iostream>
#include <fstream>
//A space for learning about the WAV format
using namespace std;

int main() {
  ifstream wavFile("a.wav", ios::binary);
  ofstream dataFile("data.wav", ios::binary);
  //Instead of these three variables, I feel like I could just use the size given by chunkSize (+ 8)
  int chunkSize = 4;
  //I didn't need the three variables
  //int soundDataSize = 4; //Subchunk2Size
  //int riffSize = 12; //Riff size 
  //int fmtSize = 4; //Subchunk1Size
  char* soundData;
  //Do I need these other two things in order to make a copy of a WAV file?
  //char* riff;
  //char* fmt; 
  uint16_t intData = 0; //In order to capture size of chunks in int form 
  if (wavFile.is_open()) {
    wavFile.seekg(4); //Should be exact, not one more or less I think
    wavFile.read((char*)(&intData), chunkSize); //Regular casting seems to work
    cout << intData << '\n';
    chunkSize = intData + 8;
    wavFile.seekg(0);
    soundData = new char[chunkSize];
    wavFile.read(soundData, chunkSize);
    dataFile.write(soundData, chunkSize);
    cout << chunkSize << "\n";
    delete[] soundData; //remember to free your data when done with it 
  }
  if (wavFile.is_open()) {
    wavFile.close();
  }
  dataFile.close();
  return 0;
}
//Notes: Supposedly, Subchunk2Size is 62561, Subchunk1Size is 4128 and ChunkSize is 6214. Is this even right? I don't think this is right, since Chunksize doesn't equal 36 + SubChunk2Size, or more precisely: 4 + (8 + SubChunk1Size) + (8 + SubChunk2Size). Chunksize is the smallest out of all of them. 
//When forgetting to change what the output file was, I actually got the data from the wav file put into the txt file, but it might be garbage data...? But I can't seem to get that data to write to the wav file. 
//Subchunk2Size is now 36340, chunkSize is 36376, and Subchunk1Size is 16. This is the right soundDataSize since it makes the equation true. 
//The error that's popping up is that of an invalid pointer for the free function, but why? This didn't happen before. Fixed by changing the soundDataSize of data, it was too small. 
//In order to make a copy of a wav file, I not only need the sound data, but I think I also need the header information. I did need those things in order to make a copy of the chosen sound programatically   