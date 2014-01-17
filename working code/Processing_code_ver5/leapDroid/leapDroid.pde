class leapDroid{
  public Serial droidPort;
  public int [] speed;
  public LeapMotionP5 droidLeap;
  public int sensitivity =2 , handCount, numberOfHand;
  public boolean handPresented;
  public Hand control; 
  
  
  leapDroid(Object obj ,String portName){
    size(1000,500, P3D);
    droidPort=new Serial(obj, portName, 9600);
    droidLeap=new LeapMotionP5(this); 
  }
}

