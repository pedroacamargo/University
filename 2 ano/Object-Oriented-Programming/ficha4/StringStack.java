import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class StringStack {
    private List<String> data;

    public StringStack() {
        this.data = new ArrayList<String>();
    }

    public String top() {
        return this.data.get(this.data.size() - 1);
    }

    public void push(String s) {
        this.data.add(s);
    }

    public void printData() {
        Iterator<String> it = this.data.iterator();
        while (it.hasNext()) {
            String nextString = (String) it.next();

            System.out.println(nextString);
        }
    }

    public void pop() {
        if (this.data.size() > 0) this.data.remove(this.data.size() - 1);
    }

    public boolean empty() {
        if (this.data.size() == 0) return true;
        else return false;
    }

    public int length() {
        return this.data.size();
    }
}
