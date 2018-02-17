/*
  Copyright (c) 2016-2017 Engimusing LLC.  All right reserved.
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#if !defined(SPI_INTERFACES_COUNT) || (SPI_INTERFACES_COUNT <= 0)
#error Incorrect Board Selected! Please select a board which supports SPI1 from the Tools->Board: menu.
#endif

#include <dataflash.h>


int buffer_counter=0;
int page_counter=0;

int lastpage=0;
 //last page written to
int pages=8; //total pages that will be used
Dataflash dflash; 



void setup()
{
  Serial.begin(115200);
  Serial.print('h');
  Serial.print('i');
  Serial.print('\n');//debug
  dflash.init(); //initialize the memory (pins are defined in dataflash.cpp


}

void loop()
{
  int j = 0;
  int i = 0;
  
  //for (i=0;i<pages;i++)
   //   {
   //     dflash.Page_Erase(i);
   //   }
  if (lastpage<pages)
  {
    for (buffer_counter=0; buffer_counter <528 ;buffer_counter++)
    {
   dflash.Buffer_Write_Byte(1,buffer_counter,33); //write to buffer 1, 1 byte at a time
    }
  
  dflash.Buffer_To_Page(1, lastpage);//write buffer 1 to the memory on page: lastpage
  lastpage++;
  //buffer 1 is no longer active - should be no 'busy' conflicts
  //this following code does not do as written in sketch
  // - but using buffer 1 puts data in correct pages!//
     for (buffer_counter=0;buffer_counter <528;buffer_counter++)
    {
    dflash.Buffer_Write_Byte(2,buffer_counter,55); //write to buffer 2, 1 byte at a time
    }
 
  dflash.Buffer_To_Page(2, lastpage);//write buffer 2 to the memory on page: lastpage
  lastpage++;
  }
  else
  {
    for (int i=0;i<=pages;i++)
    {
    dflash.Page_To_Buffer(i, 2);//copy page i to the buffer

      for(int j=0;j<528;j++) //j depends on the amount of data on the page
      {
        Serial.print(dflash.Buffer_Read_Byte(2, j)); //print the buffer data to the serial port

        Serial.print('\n');//debug 
      }
    } 
  }
}
