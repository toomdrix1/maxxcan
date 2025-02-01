#ifndef NEXTION_H
#define NEXTION_H

template<class nexSerType, class dbgSerType = nexSerType>
class NexComm
{
  public:
    NexComm(nexSerType& nexSer, dbgSerType& dbgSer): _nexSer(nexSer), _dbgSer(dbgSer) , _useDbg(true)
    {
      this->_dbgEn = this->_useDbg;
    }   
    NexComm(nexSerType& nexSer): _nexSer(nexSer), _dbgSer(nexSer) , _useDbg(false)
    {
      this->_dbgEn = this->_useDbg;
    }
    void begin(uint32_t nexBaud = 9600, uint32_t dbgBaud = 9600)
    {
      if (this->_useDbg)
      {
        this->_dbgSer.begin(dbgBaud);
        while (!this->_dbgSer);
        this->_dbgOut("Debug Serial ready!");
      }
      this->_nexSer.begin(nexBaud);
      while (!this->_nexSer);
      this->cmdWrite("");
      this->_dbgOut("Nextion Serial ready & buffer cleared!");
    }
    void dbgEnable(bool en)
    {
      if (this->_useDbg)
      {
        this->_dbgEn = en;
      } else
      {
        this->_dbgEn=false;  
      }
    }
    void cmdWrite(String cmd)
    {
      this->_nexSer.print(cmd);
      this->_nexSer.write("\xFF\xFF\xFF");
      this->_dbgOut("Command sent: " + cmd);
    }
    void stringWrite(String cmd, int val)
    {
      this->_nexSer.print(cmd);
      this->_nexSer.print("\"");
      this->_nexSer.print(val);
      this->_nexSer.print("\"");
      this->_nexSer.write("\xFF\xFF\xFF");
      this->_dbgOut("Command sent: " + cmd);
    }
  private:
    nexSerType& _nexSer;
    dbgSerType& _dbgSer;
    bool _useDbg;
    bool _dbgEn;
    void _dbgOut(String txt) {
      if (_useDbg && _dbgEn)
      {
        this->_dbgSer.println(txt);
      }
    }
};
#endif