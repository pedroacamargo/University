import java.time.LocalTime;

public class Lampada {

    private static final int ON = 0;
    private static final int OFF = 1;
    private static final int ECHO = 2;

    private int mode;
    private long tax;
    private long usage;
    private LocalTime start;
    private LocalTime end;
    
    public Lampada() {
        this.mode = OFF;
        this.usage = 0;
        this.tax = 1; // 1 euro por segundo (LOL)
        this.start = LocalTime.now();
        this.end = LocalTime.now();
    }

    public void lampON() {
        this.start = LocalTime.now();
        this.mode = ON;
    }

    public void lampOFF() {
        this.end = LocalTime.now();

        if (this.mode == ECHO) {
            this.usage += (this.start.toNanoOfDay() - this.end.toNanoOfDay()) / 2;
        } else if (this.mode == ON) {
            this.usage += this.start.toNanoOfDay() - this.end.toNanoOfDay();
        }

        this.mode = OFF;
    }

    public void lampECHO() {
        this.end = LocalTime.now();

        if (this.mode == ON) {
            this.usage += this.start.toNanoOfDay() - this.end.toNanoOfDay();
        }

        this.mode = ECHO;
    }

    public long totalConsumo() {
        long time = 0;
        
        // if on, compare with now()
        if (this.mode == ON) time = Math.abs(this.start.toNanoOfDay() - LocalTime.now().toNanoOfDay()) + this.usage;

        // if ECHO, compare with now() / 2
        if (this.mode == ECHO) time = (Math.abs(this.start.toNanoOfDay() - this.end.toNanoOfDay()) / 2) + this.usage;
        

        if (this.mode == OFF) time = usage;

        

        return time;
    }

}
