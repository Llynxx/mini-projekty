package flappyBird;

import javax.imageio.ImageIO;
import javax.sound.midi.SysexMessage;
import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

/**
 * Klasa odpowiedzialna za generowanie animacji latającego ptaka.
 */
public class BirdPanel extends JPanel {

    private BufferedImage imgBird;

    public int x, y;

    /**
     * Konstruktor klasy BirdPanel.
     * @param iterator - zmienna pomocnicza służąca do porządkowania kolejności animacji.
     */
    public BirdPanel(int iterator) {

        if(iterator == 5) {
            try {
                File input = new File("fail.png");

                imgBird = ImageIO.read(input);
            } catch (IOException ex) {

            }
        } else{
            switch(iterator%70/10+1)
            {
                case 1:
                case 7: {
                    try {
                        File input = new File("f1.png");

                        imgBird = ImageIO.read(input);
                    } catch (IOException ex) {

                    }
                    break;
                }
                case 2:
                case 6: {
                    try {
                        File input = new File("f2.png");

                        imgBird = ImageIO.read(input);
                    } catch (IOException ex) {

                    }
                    break;
                }
                case 3:
                case 5: {
                    try {
                        File input = new File("f3.png");

                        imgBird = ImageIO.read(input);
                    } catch (IOException ex) {

                    }
                    break;
                }
                case 4:{
                    try {
                        File input = new File("f4.png");

                        imgBird = ImageIO.read(input);
                    } catch (IOException ex) {

                    }
                    break;
                }
            }



        }
    }

    /**
     * Metoda przesyłająca animacje do renderowania.
     * @param g - obiekt klasy Graphics.
     * @param x - współrzędna x wyświetlanej animacji.
     * @param y - współrzędna y wyświetlanej animacji.
     */
    protected void paintComponent(Graphics g, int x, int y) {
        super.paintComponent(g);
        g.drawImage(imgBird, x, y, this);
    }

}