
// Minimal class to replace std::vector
template<typename Data>
class Vector {
  size_t d_size; // Stores no. of actually stored objects
  size_t d_capacity; // Stores allocated capacity
  Data *d_data; // Stores data
  public:
    Vector() : d_size(0), d_capacity(0), d_data(0) {}; // Default constructor
    Vector(Vector const &other) : d_size(other.d_size), d_capacity(other.d_capacity), d_data(0) { d_data = (Data *)malloc(d_capacity*sizeof(Data)); memcpy(d_data, other.d_data, d_size*sizeof(Data)); }; // Copy constuctor
    ~Vector() { free(d_data); }; // Destructor
    Vector &operator=(Vector const &other) { free(d_data); d_size = other.d_size; d_capacity = other.d_capacity; d_data = (Data *)malloc(d_capacity*sizeof(Data)); memcpy(d_data, other.d_data, d_size*sizeof(Data)); return *this; }; // Needed for memory management
    void push_back(Data const &x) { if (d_capacity == d_size) resize(); d_data[d_size++] = x; }; // Adds new value. If needed, allocates more space
    size_t size() const { return d_size; }; // Size getter
    Data const &operator[](size_t idx) const { return d_data[idx]; }; // Const getter
    Data &operator[](size_t idx) { return d_data[idx]; }; // Changeable getter
  private:
    void resize() { d_capacity = d_capacity ? d_capacity*2 : 1; Data *newdata = (Data *)malloc(d_capacity*sizeof(Data)); memcpy(newdata, d_data, d_size * sizeof(Data)); free(d_data); d_data = newdata; };// Allocates double the old space
};


// ==============================

struct ControllerEntry
{
    uint8_t pomp;
    uint8_t hh;
    uint8_t mm;
    uint8_t ss;
    uint8_t durataSec;

    String dump()
    {
       Serial.println("------");
       Serial.print(pomp);
       Serial.print(" ");
       Serial.print(hh);
       Serial.print(":");
       Serial.print(mm);
       Serial.print(":");
       Serial.print(ss);
       Serial.print(" ");
       Serial.println(durataSec);
       Serial.println("------");
    }
};


class Controller
{
  public:
    Vector<ControllerEntry> entryList;
    uint8_t state;
    uint8_t subState;
    String buf;
    ControllerEntry entry;
       
    int toInt(String &s)
    {
       char carray[6];
       s.toCharArray(carray, sizeof(carray));
       return atoi(carray); 
    }
    
    void processRow()
    {
       //Serial.print("'");
       Serial.println(buf);
      // Serial.println("'");
       
      if (state == 0)
          entry.pomp = toInt(buf);
      else  if (state == 1)
      {
        if (subState == 0) entry.hh = toInt(buf);
        else if (subState == 1) entry.mm = toInt(buf);
        else if (subState == 2) entry.ss =toInt(buf);
      }
      else
        entry.durataSec =toInt(buf);
      
    }
  
    void setup(){
      // config
        Serial.println(F("Opening config file."));

        File file = SD.open(F("config.txt"));
        if (! file) {
          Serial.print(F("error opening config file: "));
          return;
       }

      
       char ch;
       state=0;
       subState=0;
       while (file.available()) {
          ch  = (char)file.read();
          //Serial.write(ch);
          if (ch == '#')
            state = 99;
          else if (ch == '\n')
          {
            if (state < 99)
            {
                processRow(); 
                entry.dump();
                entryList.push_back(entry);
               // entry = ControllerEntry();
            }
           
            buf="";
            state=0;
            subState=0;
          } 
          else  if (ch == ',')
          {
              if (state < 99)
                processRow();
              buf="";
              state++;
          }
          else  if (ch == ':' && state == 1)
          {
              processRow();
              buf="";
              subState++;
          } 
          else 
          {
              buf+=ch;
          }
      }
      
    }
    void loop(){
      
    }
};


