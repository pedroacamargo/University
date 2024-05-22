public class SmartBulb extends SmartDevice {
    public static final int WARM = 2;
    public static final int NEUTRAL = 1;
    public static final int COLD = 0;
    private int tone;

    public SmartBulb(String id, int tone, double consumoPorHora) {
        super(id, consumoPorHora);
        this.tone = tone;
    }

    public void setTone(int t) {
        if (t>WARM) this.tone = WARM;
        else if (t<COLD) this.tone = COLD;
        else this.tone = t;
    }
    
    public int getTone() {
        return this.tone;
    }
}