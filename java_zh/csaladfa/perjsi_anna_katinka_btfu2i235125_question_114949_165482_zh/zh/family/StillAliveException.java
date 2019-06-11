package family;

import java.lang.RuntimeException;

class StillAliveException extends Exception{
	private String msg;
	public StillAliveException(String msg){
		this.msg=msg;	
	}
	public String getMsg(){
		return this.msg;
	}
}