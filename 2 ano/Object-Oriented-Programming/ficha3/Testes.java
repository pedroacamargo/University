import static org.junit.Assert.assertEquals;
import org.junit.*;


// TODO: See this
public class Testes {

    private Circulo c;
    

    // @BeforeEach
    // public void setUp() {
    //     this.c = new Circulo();
    // }

    // @AfterEach
    // public void tearDown() {
    //     this.c = null;
    // }


    @Test
    public void xIsSet() {
        this.c.setX(0);
        assertEquals(10, this.c.getX());
    }

}
