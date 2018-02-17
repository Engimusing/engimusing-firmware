///
///@file Server.h
///@brief Conatins Server class which is a Print object which can also be started.
///
///@section License
///Copyright (c) 2015 Engimusing LLC.  All right reserved.
///
///This library is free software; you can redistribute it and/or
///modify it under the terms of the GNU Lesser General Public
///License as published by the Free Software Foundation; either
///version 2.1 of the License, or (at your option) any later version.
///
///This library is distributed in the hope that it will be useful,
///but WITHOUT ANY WARRANTY; without even the implied warranty of
///MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
///See the GNU Lesser General Public License for more details.
///
///You should have received a copy of the GNU Lesser General Public
///License along with this library; if not, write to the Free Software
///Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
///
#ifndef server_h
#define server_h

///@brief Derived from Print and classes derived from are print objects that can also be started. 
class Server : public Print 
{
  public:
    ///@brief Start the server. Must be defined by the sub class
    virtual void begin() =0;
};

#endif
