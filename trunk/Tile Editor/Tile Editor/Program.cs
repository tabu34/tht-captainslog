using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace Tile_Editor
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
            //Application.Run(new frmMain());

            //Make the form
            frmMain theForm = new frmMain();

            //Display the form
            theForm.Show();

            //Start the main program loop
            while (theForm.Looping)
            {
                theForm.Render();
                Application.DoEvents();
            }
        }
    }  
}
