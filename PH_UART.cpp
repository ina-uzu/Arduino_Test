int BAUD_RATE = 9600;
String cmdData="";
String cmd[3]="";
boolean cmd_complete=false;
boolean cont_read_mode = false;
int read_rate =1;

void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  cmdData.reserve(10);  // cmd's max-length = 10 bytes
  Serial.print("\r");
}

void Read(){
  char buf[20];
  sprintf(buf, "%d.%d\r", 5,56);
  Serial.print(buf);
}

void CRead(){
   int param = cmd[1].toInt();

   /* Disable cont mode */
   if( param ==0){
    cont_read_mode=false;
   }
   
   /* Enable cont mode */
   else if( param >0 && param <100){
    read_rate = 1000*param;    
    cont_read_mode=true;
   }
}

void Cal(){
 /* Nothing to do~~ */
  
}

void parseCmd(){
  int digit = 0;
  int idx = 0 ;

  /* init */
  String sCopy = cmdData;
  cmd[0]=cmd[1]=cmd[2]="";
      
  /* parse */
  while(true)
  {
    idx = sCopy.indexOf(',');

    /* Invalid cmd*/
    if( digit==3)
      return;
      
    if(-1 != idx)
    {
      cmd[digit++] = sCopy.substring(0, idx);
      sCopy = sCopy.substring(idx+1);
     }
         
    else
    {
      cmd[digit] = sCopy;
      break;
    }
  }

  /* Perfomre this cmd */
  if( cmd[0].equals("R")){
     Read();
  }

  else if( cmd[0].equals("C")){
    CRead();
  }

  else if(cmd[0].equals("Cal")){
    Cal();
  }  
}

void loop() {

  /* If cmdData is completed, send doData to Pi */ 
  if(cmd_complete){
    parseCmd();
    cmdData ="";
    cmd_complete = false;
    digitalWrite(13, LOW);
  }
  
  /* Receive cmd 1b by 1b */ 
  if( Serial.available()){
      digitalWrite(13, HIGH);
      cmdData = Serial.readStringUntil(13); 
      cmd_complete=true;
  }

  /* continuous-reading */ 
  if( cont_read_mode ){
    Read();
  }
}  