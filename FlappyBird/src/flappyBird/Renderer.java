package flappyBird;

import javax.swing.JPanel;
import java.awt.*;

/**
 *Klasa odpowiedzialna za renderowanie obrazu wyświetlanego na ekranie.
 */
public class Renderer extends JPanel{
    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        FlappyBird.flappyBird.repaint(g);
    }
}
