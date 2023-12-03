import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class AOC2
{
    public static void main(String[] args)
    {
        try
        {
            File myObj = new File("input");
            Scanner myReader = new Scanner(myObj);

            int idsum = 0;
            int powersum = 0;
            while (myReader.hasNextLine())
            {
                String data = myReader.nextLine();

                String[] split = data.split(":", 2);
                String gamedata = split[0];
                String cubesdata = split[1];

                String[] cubessplit = cubesdata.split("; ");

                int gameid = Integer.parseInt(gamedata.split(" ", 2)[1]);

                int red = 0, green = 0, blue = 0;
                for (String cubes : cubessplit)
                {
                    String[] singlesplit = cubes.split(", ");
                    for (String single : singlesplit)
                    {
                        single = single.trim();
                        if (single.contains("red"))
                        {
                            int tmpred = Integer.parseInt(single.split(" ")[0]);
                            if (tmpred > red) red = tmpred;
                        }

                        if (single.contains("green"))
                        {
                            int tmpgreen = Integer.parseInt(single.split(" ")[0]);
                            if (tmpgreen > green) green = tmpgreen;
                        }

                        if (single.contains("blue"))
                        {
                            int tmpblue = Integer.parseInt(single.split(" ")[0]);
                            if (tmpblue > blue) blue = tmpblue;
                        }
                    }
                }
                //System.out.println(red);
                //System.out.println(green);
                //System.out.println(blue);

                if (red <= 12 && green <= 13 && blue <= 14)
                {
                    idsum += gameid;
                }

                int power = red * blue * green;
                powersum += power;
            }

            myReader.close();

            System.out.print("result a: ");
            System.out.println(idsum);

            System.out.print("result b: ");
            System.out.println(powersum);
        }
        catch (FileNotFoundException e)
        {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }
}