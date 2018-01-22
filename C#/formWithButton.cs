using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

namespace FormWithButton {
	public class Form1 : Form {
		public Form1() {
			this.Text = "Basic Form with Button";
			this.Width = 1280;
			this.Height = 720;
			Button1();
		}
		private void Button1() {
			Button button1 = new Button();
			int width = 100;
			int height = 60;
			button1.Anchor = (AnchorStyles.Bottom | AnchorStyles.Top |
				AnchorStyles.Left | AnchorStyles.Right);
			button1.Size = new Size(width, height);
			button1.Location = new Point(
				(this.Width - width) / 2,
				(this.Height - height) / 2);
			button1.Text = "Click me!";				
			button1.Click += new EventHandler(button1_Click);
			button1.Cursor = Cursors.Hand;
			Controls.Add(button1);
		}
		private void button1_Click(object sender, EventArgs e) {
			MessageBox.Show("Hello World!");
		}
	}
	public class Program {
		[STAThread]
		public static void Main(string[] args) {
			Application.EnableVisualStyles();
			Application.Run(new Form1());
		}
	}
}