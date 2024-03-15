public class Main {

    public static void main(String[] args) {
        /**
         * 1 - String stack
         * 2 - 
         */
        int QUESTION = 1; 

        if (QUESTION == 1) {
            StringStack stack = new StringStack();
            stack.push("Olá, tudo bem?");
            stack.push("Sim, está tudo bem!");
            stack.pop();
            stack.printData();
            System.out.println(stack.empty());
            System.out.println(stack.length());
        } else if (QUESTION == 2) {
            
            

        }
    }
}
