/*********************************************************************************/
/** DISCLAIMER: Este cÃ³digo foi criado e alterado durante as aulas prÃ¡ticas      */
/** de POO. Representa uma soluÃ§Ã£o em construÃ§Ã£o, com base na matÃ©ria leccionada */
/** atÃ© ao momento da sua elaboraÃ§Ã£o, e resulta da discussÃ£o e experimentaÃ§Ã£o    */
/** durante as aulas. Como tal, nÃ£o deverÃ¡ ser visto como uma soluÃ§Ã£o canÃ³nica,  */
/** ou mesmo acabada. Ã‰ disponibilizado para auxiliar o processo de estudo.      */
/** Os alunos sÃ£o encorajados a testar adequadamente o cÃ³digo fornecido e a      */
/** procurar soluÃ§Ãµes alternativas, Ã  medida que forem adquirindo mais           */
/** conhecimentos de POO.                                                        */
/*********************************************************************************/

/**
 * Classe que implementa uma LÃ¢mpada cf exercÃ­cio da Ficha 3.
 * Esta classe foi desenvolvida durante as aulas prÃ¡ticas pelo que algumas das
 * linhas de cÃ³digo decorrem de decisÃµes tomadas na altura. Existe naturalmente
 * espaÃ§o para melhorar e alterar este cÃ³digo.
 *
 * ATENÃ‡ÃƒO: a classe Lampada utiliza um enum para guardar os diferentes tipos
 * de consumo. Poderia tambÃ©m ser feito com constantes.

 *
 * @author  MaterialPOO
 * @version 20220321
 * @version 20230320
 */
 
 public class Lampada
 {
     public enum Modo {
         ON,
         OFF,
         ECO
     }
 
     private Modo modo;
 
     private double cpSOn;
     private double cpSEco;
     private double consumoTotal;
     private double consumoPeriodo;
     private long stamp;
 
     public Lampada() {
         this.modo = Modo.OFF;
         this.cpSEco = 1;
         this.cpSOn = 2;
         this.consumoTotal = 0;
         this.consumoPeriodo = 0;
         this.stamp = System.currentTimeMillis();
     }
 
     public Lampada(Lampada l){
         this.modo = l.getModo();
         this.cpSEco = l.getCpSEco();
         this.cpSOn = l.getCpSOn();
         this.consumoTotal = l.totalConsumo();
         this.consumoPeriodo = l.periodoConsumo();
         this.stamp = l.getStamp();
     }
 
     public Lampada(Modo x, double cpsE, double cpsO, double cT, double pC) {
         this.cpSEco = cpsE;
         this.cpSOn = cpsO;
         this.modo = x;
         this.consumoTotal = cT;
         this.consumoPeriodo = pC;
         this.stamp = System.currentTimeMillis();
     }
 
     public Modo getModo() {
         return modo;
     }
 
     public void setModo(Modo m) {
         this.modo = m;
     }
 
     public long getStamp() {
         return stamp;
     }
 
     public double getCpSEco(){
         return this.cpSEco;
     }
 
     public void setCpSEco(double x){
         this.cpSEco = x;
     }
 
     public double getCpSOn(){
         return this.cpSOn;
     }
 
     public void setCpSOn(double x){
         this.cpSOn = x;
     }
 
     public double getConsumoTotal() {
         return consumoTotal;
     }
 
     public void setConsumoTotal(double cT){
         this.consumoTotal = cT;
     }
 
     public double getConsumoPeriodo() {
         return consumoPeriodo;
     }
 
     public void setConsumoPeriodo(double pC){
         this.consumoPeriodo = pC;
     }
 
     public void lampON() {
         this.atualizaConsumo();
         this.modo = Modo.ON;
     }
 
     public void lampOFF() {
         this.atualizaConsumo();
         this.modo = Modo.OFF;
     }
 
     public void lampECO() {
         this.atualizaConsumo();
         this.modo = Modo.ECO;
     }
 
     public void resetPeriodo(){
         atualizaConsumo();
         this.consumoPeriodo = 0;
     }
 
     public double periodoConsumo(){
         atualizaConsumo();
         return consumoPeriodo;
     }
     public double totalConsumo() {
         atualizaConsumo();
         return consumoTotal;
     }
 
     private void atualizaConsumo() {
         long periodo = System.currentTimeMillis() - stamp;
 
         if(this.modo == Modo.ON) {
             this.consumoTotal += cpSOn *periodo;
             this.consumoPeriodo += cpSOn *periodo;
         } else if(this.modo == Modo.ECO) {
             this.consumoTotal += cpSEco *periodo;
             this.consumoPeriodo += cpSEco *periodo;
         }
 
         this.stamp = System.currentTimeMillis();
     }
 
     public Lampada clone(){
         return new Lampada(this);
     }
 
     @Override
     public String toString() {
         StringBuilder sb = new StringBuilder();
         sb.append("Lampada: ").append(this.modo)
                 .append("\nConsumo por segundo Eco: ").append(this.cpSEco)
                 .append("\nConsumo por segundo On: ").append(this.cpSOn)
                 .append("\nConsumoTotal: ").append(this.consumoTotal)
                 .append("\nInicio de ultimo consumo: ").append(this.consumoPeriodo);
         return sb.toString();
     }
 
     public boolean equals(Object o){
         if (this==o) return true;
         if ((o == null) || (this.getClass() != o.getClass())) return false;
 
         Lampada l = (Lampada) o;
         return l.getModo() == this.modo &&
                 l.getCpSOn() == this.cpSOn &&
                 l.getCpSEco() == this.cpSEco &&
                 l.getConsumoTotal() == this.consumoTotal &&
                 l.getConsumoPeriodo() == this.consumoPeriodo &&
                 l.getStamp() == this.stamp;
     }
 }