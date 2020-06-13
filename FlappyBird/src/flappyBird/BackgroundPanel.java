package flappyBird;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

/**
 * Klasa odpowiedzialna za generowanie tła w grze.
 */
public class BackgroundPanel extends JPanel {

    private BufferedImage image;

    /**
     * Konstruktor klasy BackgroundPanel.
     */
    public BackgroundPanel() {
        try {

            File input = new File("land.png");

            image = ImageIO.read(input);

        } catch (IOException ex) {

        }
    }

    /**
     * Metoda przesyłająca animacje do renderowania.
     * @param g - obiekt klasy Graphics
     */
    @Override
    protected void paintComponent(Graphics g) {
        //  System.out.println(image.getData());
        super.paintComponent(g);
        g.drawImage(image, 0, 0, this);
    }

}