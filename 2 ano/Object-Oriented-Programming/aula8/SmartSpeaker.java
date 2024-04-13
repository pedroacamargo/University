 

/*********************************************************************************/
/** DISCLAIMER: Este código foi criado e alterado durante as aulas práticas      */
/** de POO. Representa uma solução em construção, com base na matéria leccionada */ 
/** até ao momento da sua elaboração, e resulta da discussão e experimentação    */
/** durante as aulas. Como tal, não deverá ser visto como uma solução canónica,  */
/** ou mesmo acabada. É disponibilizado para auxiliar o processo de estudo.      */
/** Os alunos são encorajados a testar adequadamente o código fornecido e a      */
/** procurar soluções alternativas, à medida que forem adquirindo mais           */
/** conhecimentos de POO.                                                        */
/*********************************************************************************/

/**
 * Um SmartSpeaker é um SmartDevice que além de ligar e desligar permite também
 * reproduzir som.
 * Consegue ligar-se a um canal (por simplificação uma rádio online) e permite
 * a regulação do seu nível de volume.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class SmartSpeaker extends SmartDevice {
    public static final int MAX = 20; //volume máximo
    
    private int volume;
    private String channel;


    /**
     * Constructor for objects of class SmartSpeaker
     */
    public SmartSpeaker() {
        super();
        // initialise instance variables
        this.volume = 10;
        this.channel = "";
    }

    public SmartSpeaker(String s) {
        super(s);
        // initialise instance variables
        this.volume = 10;
        this.channel = "";
    }



    public SmartSpeaker(String cod, String channel, int i) {
        super(cod);
        // initialise instance variables
        this.volume = i;
        this.channel = channel;
    }

    public void volumeUp() {
        if (this.volume<MAX) this.volume++;
    }

    public void volumeDown() {
        if (this.volume>0) this.volume--;
    }

    public int getVolume() {return 0;}
    
    public String getChannel() {return "";}
    
    public void setChannel(String c) {}

}
