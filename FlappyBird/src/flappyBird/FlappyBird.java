package flappyBird;

import com.sun.java.swing.plaf.windows.WindowsInternalFrameTitlePane;
import sun.applet.AppletResourceLoader;
import sun.audio.AudioData;
import sun.audio.AudioPlayer;
import sun.audio.AudioStream;
import sun.audio.ContinuousAudioDataStream;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Random;

/**
 * Klasa odpowiedzialna za całokształt aplikacji.
 */
public class FlappyBird implements ActionListener, MouseListener, KeyListener {

    public static FlappyBird flappyBird;

    public final int WIDTH = 1200, HEIGHT = 800;

    public Renderer renderer;

    public Rectangle bird;

    public ArrayList<Rectangle> columns;

    public int ticks, yMotion, score, highscore, iterator = 0;

    public Random rand;

    public boolean gameOver, started, newhigh, inters;

    /**
     *Konstruktor klasy FlappyBird.
     */
    public FlappyBird() {
        JFrame jframe = new JFrame();
        Timer timer = new Timer(20, this);
        renderer = new Renderer();
        rand = new Random();
        jframe.add(renderer);
        jframe.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        jframe.setSize(WIDTH, HEIGHT);
        jframe.addMouseListener(this);
        jframe.addKeyListener(this);
        jframe.setResizable(false);
        jframe.setTitle("Flappy Bird");
        jframe.setIconImage(Toolkit.getDefaultToolkit().getImage(getClass().getResource("4cent.png")));
        jframe.setVisible(true);
        highscore = 0;
        bird = new Rectangle(WIDTH/2 - 10 , HEIGHT/2 - 10, 40, 40);
        columns = new ArrayList<Rectangle>();

        addColumn(true);
        addColumn(true);
        addColumn(true);
        addColumn(true);

        timer.start();
    }

    /**
     * Metoda generująca nowe kolumny.
     * @param start - zmienna typu boolean określająca, czy gracz rozpoczął nową turę.
     */
    public void addColumn(boolean start){
        int space = 300;
        int width = 100;
        int height = 50 + rand.nextInt(300);

        if(start) {
            columns.add(new Rectangle(WIDTH + width + columns.size() * 300, HEIGHT - height - 126, width, height));
            columns.add(new Rectangle(WIDTH + width + (columns.size() - 1) * 300, 0, width, HEIGHT - height - space));
        }
        else {
            columns.add(new Rectangle(columns.get(columns.size() - 1).x + 600, HEIGHT - height - 126, width, height));
            columns.add(new Rectangle(columns.get(columns.size() - 1).x, 0, width, HEIGHT - height - space));
        }
    }

    /**
     * Metoda wypełniająca kolumny odpowiednim kolorem.
     * @param g obiekt klasy Graphics.
     * @param column - obiekt klasy Rectangle będący kolumną w grze.
     */
    public void paintColumn(Graphics g, Rectangle column){
        g.setColor(Color.green.darker().darker());
        g.fillRect(column.x, column.y, column.width, column.height);
    }

    /**
     * Metoda odpowiadająca za generowanie i obsługę odpowiednich elementów przy rozpoczęciu nowej gry.
     */
    public void jump(){

        if(gameOver){

            bird = new Rectangle(WIDTH/2 - 10 , HEIGHT/2 - 10, 40, 40);
            columns.clear();
            columns = new ArrayList<Rectangle>();
            newhigh = false;
            addColumn(true);
            addColumn(true);
            addColumn(true);
            addColumn(true);

            gameOver = false;
            inters = false;
        }

        if(!started){
            started = true;
            score = 0;
            ticks = 0;
        }

        else if(!gameOver){
            if(yMotion > 0){
                yMotion = 0;
            }

            yMotion -=10;
        }
    }

    /**
     * Metoda generująca oraz usuwająca kolumny. Sprawdza kolizje ptaka z obiektami powodującymi koniec gry.
     * @param e
     */
    @Override
    public void actionPerformed(ActionEvent e) {

        int speed = 15;

        if(gameOver) {
            if(score > highscore){
                highscore = score;
                newhigh = true;
            }
            speed = 0;
            ticks = 0;

        }
        if(!gameOver && started){
            score = ticks/10;
        }

        ticks++;
        if(started) {
            for (int i = 0; i < columns.size(); i++) {

                Rectangle column = columns.get(i);

                column.x -= speed;
            }

            if (ticks % 2 == 0 && yMotion < 15) {
                if(gameOver){
                    yMotion = 0;
                }
                else {
                    yMotion += 2;
                }
            }

            for (int i = 0; i < columns.size(); i++) {
                Rectangle column = columns.get(i);

                if (column.x + column.width < 0) {
                    columns.remove(column);

                    if (column.y == 0) {
                        addColumn(false);
                    }
                }
            }

            bird.y += yMotion;

            for (Rectangle column : columns) {
                if (column.intersects(bird)) {
                    inters = true;
                    gameOver = true;
                    if (bird.x <= column.x)
                    {
                        bird.x = column.x - bird.width;

                    }
                    else
                    {
                        if (column.y != 0)
                        {
                            bird.y = column.y - bird.height;
                        }
                        else if (bird.y < column.height)
                        {
                            bird.y = column.height;
                        }
                    }
                }
            }

            if (bird.y >= HEIGHT - 126 - bird.width) {
                gameOver = true;
                bird.y = HEIGHT - 126 - bird.height;
            }

            if (bird.y < 0) {
                gameOver = true;
                bird.y = 0;
            }



            if(inters){
                if(yMotion < 0){
                    yMotion = 0;
                }
                if(yMotion == 0){
                    yMotion += 4;
                }


            }
        }
        renderer.repaint();
    }


    /**
     * Metoda odpowiedzialna za generowanie odpowiednich elementów obrazu oraz napisów.
     * @param g - obiekt klasy Graphics
     */
    public void repaint(Graphics g) {
//
//        g.fillRect(0, 0, WIDTH, HEIGHT);
//
//        g.setColor(Color.darkGray);
//        g.fillRect(0, HEIGHT - 120, WIDTH, 120);
//
//        g.setColor(Color.green);
//        g.fillRect(0, HEIGHT - 120, WIDTH, 20);

        BackgroundPanel bcgp = new BackgroundPanel();
        bcgp.paintComponent(g);

        iterator++;
        if(gameOver) {
            iterator = 5;
        }
        BirdPanel bird = new BirdPanel(iterator);
        bird.paintComponent(g, flappyBird.bird.x, flappyBird.bird.y);


//        g.setColor(Color.red);
//        g.fillRect(bird.x, bird.y, bird.width, bird.height);

        for(Rectangle column : columns) {
            paintColumn(g, column);
        }

        g.setColor(Color.black);
        g.setFont(new Font("Arial", 3, 100));

        if(!started) {
            g.drawString("Click to start", 260, HEIGHT/2 - 50);
        }

        if(gameOver) {
            g.drawString("Game Over!", 320, HEIGHT/2 - 150);
        }

        g.setColor(Color.black);
        g.setFont(new Font("Arial", 3, 100));

        if(!gameOver && started){
            g.drawString(String.valueOf(score), 558, 85);
        }
        if(gameOver){
            g.drawString("Your score: ", 270, HEIGHT/2 + 100);
            g.drawString(String.valueOf(score), 840, HEIGHT/2 + 100);
            g.setFont(new Font("Arial", 3, 30));
            g.drawString("Highest score: ", 0, 26);
            g.drawString(String.valueOf(highscore), 220, 26);
        }
        g.setFont(new Font("Arial", 3, 100));
        if(gameOver && newhigh){
            g.drawString("New highest score!", 135, HEIGHT/2 - 25);
        }

    }

    public static void main(String[] args) {
        flappyBird = new FlappyBird();
    }


    @Override
    public void mouseClicked(MouseEvent e){

    }

    /**
     * Metoda sprawdzająca wciśnięcie przycisku myszy i wywołanie przy tym odpowiedniej metody.
     * @param e
     */
    @Override
    public void mousePressed(MouseEvent e) {
        jump();
    }

    @Override
    public void mouseReleased(MouseEvent e) {

    }

    @Override
    public void mouseEntered(MouseEvent e) {

    }

    @Override
    public void mouseExited(MouseEvent e) {

    }


    @Override
    public void keyTyped(KeyEvent e) {

    }

    /**
     * Metoda sprawdzająca wciśnięcie odpowiedniego przycisku na klawiaturze i wywołanie przy tym odpowiedniej metody.
     * @param e - objekt klasy KeyEvent
     */
    @Override
    public void keyPressed(KeyEvent e) {
        if(e.getKeyCode() == KeyEvent.VK_SPACE)
            jump();
        if(e.getKeyCode() == KeyEvent.VK_ESCAPE && gameOver == true){
            System.exit(0);
        }
    }

    @Override
    public void keyReleased(KeyEvent e) {

    }
}
