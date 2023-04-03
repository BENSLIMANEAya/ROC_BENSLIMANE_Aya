using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;
using ExtendedSerialPort;

namespace RobotInterface
{
    /// <summary>
    /// Logique d'interaction pour MainWindow.xaml
    /// </summary>

   
    public partial class MainWindow : Window
    {
        
        ReliableSerialPort serialPort1;
        DispatcherTimer timerAffichage = new DispatcherTimer();
        string receivedText = "" ;
        Robot robot = new Robot();


        public MainWindow()
        {
            InitializeComponent();

            serialPort1 = new ReliableSerialPort("COM4", 115200, System.IO.Ports.Parity.None, 8, System.IO.Ports.StopBits.One);
            serialPort1.OnDataReceivedEvent += SerialPort1_OnDataReceivedEvent;
            serialPort1.Open();

            timerAffichage = new DispatcherTimer();
            timerAffichage.Interval = new TimeSpan(0, 0, 0, 0, 100);
            timerAffichage.Tick += TimerAffichage_Tick;
            timerAffichage.Start();
        }

        private void TimerAffichage_Tick(object sender,EventArgs e)
        {
            if (receivedText != "")
            {
                textBoxReception.Text += receivedText;
                receivedText = "";
            }

        }

        private void SerialPort1_OnDataReceivedEvent(object sender, DataReceivedArgs e)
        {
            // throw new NotImplementedException();
            receivedText += Encoding.UTF8.GetString(e.Data, 0, e.Data.Length);
        }

        private void buttonEnvoyer_Click(object sender, RoutedEventArgs e)
        {
            byte[] bytelist = new byte[20];
            for (int i=0;i<bytelist.Length;i++)
            { bytelist[i] = (byte)(8 * i);

            }
            serialPort1.Write(bytelist,0, bytelist.Length);
        }


        private void SendMessage()
        {
            //string objTextBox = textBoxEmission.Text;
            //textBoxReception.Text += objTextBox + "\n";
            serialPort1.WriteLine(textBoxEmission.Text);
            textBoxEmission.Text = " ";



        }
        private void textBoxEmission_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                SendMessage();
            }
        }

        private void buttonRéception_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
