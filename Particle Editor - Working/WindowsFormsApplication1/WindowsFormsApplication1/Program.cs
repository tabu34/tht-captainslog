﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

using SGD;

namespace WindowsFormsApplication1
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            //Application.Run(new Form1());

            Form1 myform = new Form1();
            myform.Show();

            while (myform.Looping)
            {
                myform.DoWork();
                Application.DoEvents();
            }
        }
    }
}
