import java.util.LinkedList;

class Logger{
    private LinkedList<String> list = new LinkedList<>();
    private Logger(){

    }
    private static Logger logger;
    public static Logger getLogger(){
        if(logger == null){
            logger = new Logger();
        }
        return logger;
    }
    public void addLog(String log){
        list.add(log);
    }
    public void getLog(){
        for(String log:list){
            System.out.println(log);
        }
    }
}

class dummy{
    Logger logger;
    dummy(){
         logger=Logger.getLogger();
         logger.addLog("Hello dummy");
    }

}

public class Main {
    public static void main(String[] args) {
        Logger logger=Logger.getLogger();
        logger.addLog("Hello World");
        new dummy();
        logger.getLog();
    }
}