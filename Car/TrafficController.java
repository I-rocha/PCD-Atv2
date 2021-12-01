public class TrafficController {

	private boolean bridgeIsOccupied = false;

	public synchronized boolean tryBridge(){
		
		if(!bridgeIsOccupied){
			bridgeIsOccupied = true;
			return true;	
		}
		else{
			return false;
		}
	}

	public synchronized void freeBridge(){
		bridgeIsOccupied = false;
	}

    public synchronized void enterLeft() {
		try{
			while (!tryBridge()){
				wait();
			}
		}catch(InterruptedException e){
			e.printStackTrace();
		}
	}
    public synchronized void enterRight() {
		try{
			while(!tryBridge())
				wait();
		}catch(InterruptedException e){
			e.printStackTrace();
		}

	}
    public synchronized void leaveLeft() {
		freeBridge();
		notify();
	}
    public synchronized void leaveRight() {
		freeBridge();
		notify();
	}

}
