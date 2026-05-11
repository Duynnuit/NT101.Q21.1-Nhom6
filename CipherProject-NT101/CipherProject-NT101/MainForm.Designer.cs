namespace CipherProject_NT101
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();

            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPlayFair = new System.Windows.Forms.TabPage();
            this.tabRSA = new System.Windows.Forms.TabPage();

            // PlayFair controls
            this.grpPFKey = new System.Windows.Forms.GroupBox();
            this.lblPFKey = new System.Windows.Forms.Label();
            this.txtPFKey = new System.Windows.Forms.TextBox();
            this.lblPFMatrix = new System.Windows.Forms.Label();
            this.txtPFMatrix = new System.Windows.Forms.TextBox();

            this.grpPFInput = new System.Windows.Forms.GroupBox();
            this.lblPFPlain = new System.Windows.Forms.Label();
            this.txtPFPlain = new System.Windows.Forms.TextBox();
            this.lblPFPrepared = new System.Windows.Forms.Label();
            this.txtPFPrepared = new System.Windows.Forms.TextBox();
            this.lblPFCipher = new System.Windows.Forms.Label();
            this.txtPFCipher = new System.Windows.Forms.TextBox();
            this.btnPFEncrypt = new System.Windows.Forms.Button();
            this.btnPFDecrypt = new System.Windows.Forms.Button();
            this.btnPFClear = new System.Windows.Forms.Button();

            // RSA controls
            this.grpRSAKey = new System.Windows.Forms.GroupBox();
            this.lblRSAP = new System.Windows.Forms.Label();
            this.txtRSAP = new System.Windows.Forms.TextBox();
            this.lblRSAQ = new System.Windows.Forms.Label();
            this.txtRSAQ = new System.Windows.Forms.TextBox();
            this.btnRSAGen = new System.Windows.Forms.Button();
            this.lblRSAN = new System.Windows.Forms.Label();
            this.txtRSAN = new System.Windows.Forms.TextBox();
            this.lblRSAPhi = new System.Windows.Forms.Label();
            this.txtRSAPhi = new System.Windows.Forms.TextBox();
            this.lblRSAE = new System.Windows.Forms.Label();
            this.txtRSAE = new System.Windows.Forms.TextBox();
            this.lblRSAD = new System.Windows.Forms.Label();
            this.txtRSAD = new System.Windows.Forms.TextBox();
            this.lblRSAKeyNote = new System.Windows.Forms.Label();

            this.grpRSAEnc = new System.Windows.Forms.GroupBox();
            this.lblRSAM = new System.Windows.Forms.Label();
            this.txtRSAM = new System.Windows.Forms.TextBox();
            this.lblRSAC = new System.Windows.Forms.Label();
            this.txtRSAC = new System.Windows.Forms.TextBox();
            this.lblRSAFormula = new System.Windows.Forms.Label();
            this.txtRSAResult = new System.Windows.Forms.TextBox();
            this.btnRSAEnc = new System.Windows.Forms.Button();
            this.btnRSADec = new System.Windows.Forms.Button();
            this.btnRSAClear = new System.Windows.Forms.Button();

            // ToolTip
            this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);

            // Suspend layout to avoid repeated layout passes
            this.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.tabPlayFair.SuspendLayout();
            this.grpPFKey.SuspendLayout();
            this.grpPFInput.SuspendLayout();
            this.tabRSA.SuspendLayout();
            this.grpRSAKey.SuspendLayout();
            this.grpRSAEnc.SuspendLayout();

            // ── tabControl1 ──────────────────────────────────────────
            this.tabControl1.Controls.Add(this.tabPlayFair);
            this.tabControl1.Controls.Add(this.tabRSA);
            this.tabControl1.Location = new System.Drawing.Point(8, 8);
            this.tabControl1.Size = new System.Drawing.Size(666, 480);
            this.tabControl1.TabIndex = 0;
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.AccessibleName = "MainCipherTabs";

            // ── tabPlayFair ──────────────────────────────────────────
            this.tabPlayFair.Text = "Mã hoá PlayFair";
            this.tabPlayFair.Padding = new System.Windows.Forms.Padding(6);
            this.tabPlayFair.Controls.Add(this.grpPFKey);
            this.tabPlayFair.Controls.Add(this.grpPFInput);
            this.tabPlayFair.TabIndex = 0;

            //  grpPFKey
            this.grpPFKey.Text = "Khoá và Ma trận";
            this.grpPFKey.Location = new System.Drawing.Point(8, 8);
            this.grpPFKey.Size = new System.Drawing.Size(200, 430);
            this.grpPFKey.Controls.Add(this.lblPFKey);
            this.grpPFKey.Controls.Add(this.txtPFKey);
            this.grpPFKey.Controls.Add(this.lblPFMatrix);
            this.grpPFKey.Controls.Add(this.txtPFMatrix);
            this.grpPFKey.TabIndex = 0;

            this.lblPFKey.Text = "Khoá (Key):";
            this.lblPFKey.Location = new System.Drawing.Point(8, 22);
            this.lblPFKey.Size = new System.Drawing.Size(180, 16);

            this.txtPFKey.Location = new System.Drawing.Point(8, 40);
            this.txtPFKey.Size = new System.Drawing.Size(180, 22);
            this.txtPFKey.Text = "KEYWORD";
            this.txtPFKey.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.txtPFKey.TextChanged += new System.EventHandler(this.txtPFKey_TextChanged);
            this.txtPFKey.TabIndex = 1;
            this.txtPFKey.AccessibleName = "PlayfairKey";
            this.toolTip1.SetToolTip(this.txtPFKey, "Enter a keyword (letters only).");

            this.lblPFMatrix.Text = "Ma trận 5×5:";
            this.lblPFMatrix.Location = new System.Drawing.Point(8, 72);
            this.lblPFMatrix.Size = new System.Drawing.Size(180, 16);

            this.txtPFMatrix.Location = new System.Drawing.Point(8, 90);
            this.txtPFMatrix.Size = new System.Drawing.Size(180, 330);
            this.txtPFMatrix.Multiline = true;
            this.txtPFMatrix.ReadOnly = true;
            this.txtPFMatrix.Font = new System.Drawing.Font("Courier New", 13f, System.Drawing.FontStyle.Bold);
            this.txtPFMatrix.BackColor = System.Drawing.SystemColors.Control;
            this.txtPFMatrix.ScrollBars = System.Windows.Forms.ScrollBars.None;
            this.txtPFMatrix.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.txtPFMatrix.TabStop = false;
            this.txtPFMatrix.TabIndex = 2;

            //  grpPFInput
            this.grpPFInput.Text = "Nhập / Kết quả";
            this.grpPFInput.Location = new System.Drawing.Point(216, 8);
            this.grpPFInput.Size = new System.Drawing.Size(432, 430);
            this.grpPFInput.Controls.Add(this.lblPFPlain);
            this.grpPFInput.Controls.Add(this.txtPFPlain);
            this.grpPFInput.Controls.Add(this.btnPFEncrypt);
            this.grpPFInput.Controls.Add(this.btnPFDecrypt);
            this.grpPFInput.Controls.Add(this.btnPFClear);
            this.grpPFInput.Controls.Add(this.lblPFPrepared);
            this.grpPFInput.Controls.Add(this.txtPFPrepared);
            this.grpPFInput.Controls.Add(this.lblPFCipher);
            this.grpPFInput.Controls.Add(this.txtPFCipher);
            this.grpPFInput.TabIndex = 1;

            this.lblPFPlain.Text = "Bản rõ (Plain text):";
            this.lblPFPlain.Location = new System.Drawing.Point(10, 22);
            this.lblPFPlain.Size = new System.Drawing.Size(410, 16);

            this.txtPFPlain.Location = new System.Drawing.Point(10, 40);
            this.txtPFPlain.Size = new System.Drawing.Size(410, 70);
            this.txtPFPlain.Multiline = true;
            this.txtPFPlain.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtPFPlain.TabIndex = 3;

            this.btnPFEncrypt.Text = "Mã hoá";
            this.btnPFEncrypt.Location = new System.Drawing.Point(10, 120);
            this.btnPFEncrypt.Size = new System.Drawing.Size(90, 26);
            this.btnPFEncrypt.Click += new System.EventHandler(this.btnPFEncrypt_Click);
            this.btnPFEncrypt.TabIndex = 4;
            this.toolTip1.SetToolTip(this.btnPFEncrypt, "Encrypt the plain text using the PlayFair key.");

            this.btnPFDecrypt.Text = "Giải mã";
            this.btnPFDecrypt.Location = new System.Drawing.Point(108, 120);
            this.btnPFDecrypt.Size = new System.Drawing.Size(90, 26);
            this.btnPFDecrypt.Click += new System.EventHandler(this.btnPFDecrypt_Click);
            this.btnPFDecrypt.TabIndex = 5;

            this.btnPFClear.Text = "Xoá";
            this.btnPFClear.Location = new System.Drawing.Point(206, 120);
            this.btnPFClear.Size = new System.Drawing.Size(70, 26);
            this.btnPFClear.Click += new System.EventHandler(this.btnPFClear_Click);
            this.btnPFClear.TabIndex = 6;

            this.lblPFPrepared.Text = "Văn bản sau chuẩn bị (digrams):";
            this.lblPFPrepared.Location = new System.Drawing.Point(10, 158);
            this.lblPFPrepared.Size = new System.Drawing.Size(410, 16);

            this.txtPFPrepared.Location = new System.Drawing.Point(10, 176);
            this.txtPFPrepared.Size = new System.Drawing.Size(410, 50);
            this.txtPFPrepared.Multiline = true;
            this.txtPFPrepared.ReadOnly = true;
            this.txtPFPrepared.Font = new System.Drawing.Font("Courier New", 10f);
            this.txtPFPrepared.BackColor = System.Drawing.SystemColors.Control;
            this.txtPFPrepared.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtPFPrepared.TabStop = false;
            this.txtPFPrepared.TabIndex = 7;

            this.lblPFCipher.Text = "Kết quả:";
            this.lblPFCipher.Location = new System.Drawing.Point(10, 238);
            this.lblPFCipher.Size = new System.Drawing.Size(410, 16);

            this.txtPFCipher.Location = new System.Drawing.Point(10, 256);
            this.txtPFCipher.Size = new System.Drawing.Size(410, 156);
            this.txtPFCipher.Multiline = true;
            this.txtPFCipher.ReadOnly = true;
            this.txtPFCipher.Font = new System.Drawing.Font("Courier New", 11f, System.Drawing.FontStyle.Bold);
            this.txtPFCipher.BackColor = System.Drawing.SystemColors.Control;
            this.txtPFCipher.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtPFCipher.TabStop = false;
            this.txtPFCipher.TabIndex = 8;

            // ── tabRSA ───────────────────────────────────────────────
            this.tabRSA.Text = "Mã hoá RSA";
            this.tabRSA.Padding = new System.Windows.Forms.Padding(6);
            this.tabRSA.Controls.Add(this.grpRSAKey);
            this.tabRSA.Controls.Add(this.grpRSAEnc);
            this.tabRSA.TabIndex = 1;

            //  grpRSAKey
            this.grpRSAKey.Text = "Sinh khoá RSA";
            this.grpRSAKey.Location = new System.Drawing.Point(8, 8);
            this.grpRSAKey.Size = new System.Drawing.Size(648, 176);
            this.grpRSAKey.Controls.Add(this.lblRSAP);
            this.grpRSAKey.Controls.Add(this.txtRSAP);
            this.grpRSAKey.Controls.Add(this.lblRSAQ);
            this.grpRSAKey.Controls.Add(this.txtRSAQ);
            this.grpRSAKey.Controls.Add(this.btnRSAGen);
            this.grpRSAKey.Controls.Add(this.lblRSAN);
            this.grpRSAKey.Controls.Add(this.txtRSAN);
            this.grpRSAKey.Controls.Add(this.lblRSAPhi);
            this.grpRSAKey.Controls.Add(this.txtRSAPhi);
            this.grpRSAKey.Controls.Add(this.lblRSAE);
            this.grpRSAKey.Controls.Add(this.txtRSAE);
            this.grpRSAKey.Controls.Add(this.lblRSAD);
            this.grpRSAKey.Controls.Add(this.txtRSAD);
            this.grpRSAKey.Controls.Add(this.lblRSAKeyNote);
            this.grpRSAKey.TabIndex = 0;

            // hàng 1 — p, q, nút
            this.lblRSAP.Text = "p (số nguyên tố):";
            this.lblRSAP.Location = new System.Drawing.Point(10, 26);
            this.lblRSAP.Size = new System.Drawing.Size(110, 16);

            this.txtRSAP.Location = new System.Drawing.Point(124, 24);
            this.txtRSAP.Size = new System.Drawing.Size(80, 22);
            this.txtRSAP.Text = "61";
            this.txtRSAP.TabIndex = 1;
            this.toolTip1.SetToolTip(this.txtRSAP, "First prime (p).");

            this.lblRSAQ.Text = "q (số nguyên tố):";
            this.lblRSAQ.Location = new System.Drawing.Point(220, 26);
            this.lblRSAQ.Size = new System.Drawing.Size(110, 16);

            this.txtRSAQ.Location = new System.Drawing.Point(334, 24);
            this.txtRSAQ.Size = new System.Drawing.Size(80, 22);
            this.txtRSAQ.Text = "53";
            this.txtRSAQ.TabIndex = 2;
            this.toolTip1.SetToolTip(this.txtRSAQ, "Second prime (q).");

            this.btnRSAGen.Text = "Sinh khoá";
            this.btnRSAGen.Location = new System.Drawing.Point(430, 22);
            this.btnRSAGen.Size = new System.Drawing.Size(88, 26);
            this.btnRSAGen.Click += new System.EventHandler(this.btnRSAGen_Click);
            this.btnRSAGen.TabIndex = 3;

            // hàng 2 — n, phi
            this.lblRSAN.Text = "n = p × q:";
            this.lblRSAN.Location = new System.Drawing.Point(10, 64);
            this.lblRSAN.Size = new System.Drawing.Size(110, 16);

            this.txtRSAN.Location = new System.Drawing.Point(124, 62);
            this.txtRSAN.Size = new System.Drawing.Size(80, 22);
            this.txtRSAN.ReadOnly = true;
            this.txtRSAN.BackColor = System.Drawing.SystemColors.Control;
            this.txtRSAN.TabStop = false;
            this.txtRSAN.TabIndex = 4;

            this.lblRSAPhi.Text = "φ(n) = (p-1)(q-1):";
            this.lblRSAPhi.Location = new System.Drawing.Point(220, 64);
            this.lblRSAPhi.Size = new System.Drawing.Size(120, 16);

            this.txtRSAPhi.Location = new System.Drawing.Point(344, 62);
            this.txtRSAPhi.Size = new System.Drawing.Size(80, 22);
            this.txtRSAPhi.ReadOnly = true;
            this.txtRSAPhi.BackColor = System.Drawing.SystemColors.Control;
            this.txtRSAPhi.TabStop = false;
            this.txtRSAPhi.TabIndex = 5;

            // hàng 3 — e, d
            this.lblRSAE.Text = "e (khoá công khai):";
            this.lblRSAE.Location = new System.Drawing.Point(10, 102);
            this.lblRSAE.Size = new System.Drawing.Size(118, 16);

            this.txtRSAE.Location = new System.Drawing.Point(132, 100);
            this.txtRSAE.Size = new System.Drawing.Size(80, 22);
            this.txtRSAE.ReadOnly = true;
            this.txtRSAE.BackColor = System.Drawing.SystemColors.Control;
            this.txtRSAE.TabStop = false;
            this.txtRSAE.TabIndex = 6;

            this.lblRSAD.Text = "d (khoá bí mật):";
            this.lblRSAD.Location = new System.Drawing.Point(230, 102);
            this.lblRSAD.Size = new System.Drawing.Size(110, 16);

            this.txtRSAD.Location = new System.Drawing.Point(344, 100);
            this.txtRSAD.Size = new System.Drawing.Size(80, 22);
            this.txtRSAD.ReadOnly = true;
            this.txtRSAD.BackColor = System.Drawing.SystemColors.Control;
            this.txtRSAD.TabStop = false;
            this.txtRSAD.TabIndex = 7;

            // ghi chú
            this.lblRSAKeyNote.Text = "Khoá công khai: (e, n)     |     Khoá bí mật: (d, n)";
            this.lblRSAKeyNote.Location = new System.Drawing.Point(10, 140);
            this.lblRSAKeyNote.Size = new System.Drawing.Size(620, 16);
            this.lblRSAKeyNote.ForeColor = System.Drawing.SystemColors.GrayText;

            //  grpRSAEnc
            this.grpRSAEnc.Text = "Mã hoá / Giải mã";
            this.grpRSAEnc.Location = new System.Drawing.Point(8, 192);
            this.grpRSAEnc.Size = new System.Drawing.Size(648, 244);
            this.grpRSAEnc.Controls.Add(this.lblRSAM);
            this.grpRSAEnc.Controls.Add(this.txtRSAM);
            this.grpRSAEnc.Controls.Add(this.lblRSAC);
            this.grpRSAEnc.Controls.Add(this.txtRSAC);
            this.grpRSAEnc.Controls.Add(this.btnRSAEnc);
            this.grpRSAEnc.Controls.Add(this.btnRSADec);
            this.grpRSAEnc.Controls.Add(this.btnRSAClear);
            this.grpRSAEnc.Controls.Add(this.lblRSAFormula);
            this.grpRSAEnc.Controls.Add(this.txtRSAResult);
            this.grpRSAEnc.TabIndex = 1;

            this.lblRSAM.Text = "Bản rõ M (số nguyên, M < n):";
            this.lblRSAM.Location = new System.Drawing.Point(10, 26);
            this.lblRSAM.Size = new System.Drawing.Size(180, 16);

            this.txtRSAM.Location = new System.Drawing.Point(194, 24);
            this.txtRSAM.Size = new System.Drawing.Size(100, 22);
            this.txtRSAM.Text = "65";
            this.txtRSAM.TabIndex = 8;

            this.lblRSAC.Text = "Bản mã C:";
            this.lblRSAC.Location = new System.Drawing.Point(310, 26);
            this.lblRSAC.Size = new System.Drawing.Size(68, 16);

            this.txtRSAC.Location = new System.Drawing.Point(382, 24);
            this.txtRSAC.Size = new System.Drawing.Size(100, 22);
            this.txtRSAC.ReadOnly = true;
            this.txtRSAC.BackColor = System.Drawing.SystemColors.Control;
            this.txtRSAC.TabStop = false;
            this.txtRSAC.TabIndex = 9;

            this.btnRSAEnc.Text = "Mã hoá";
            this.btnRSAEnc.Location = new System.Drawing.Point(10, 58);
            this.btnRSAEnc.Size = new System.Drawing.Size(90, 26);
            this.btnRSAEnc.Click += new System.EventHandler(this.btnRSAEnc_Click);
            this.btnRSAEnc.TabIndex = 10;

            this.btnRSADec.Text = "Giải mã";
            this.btnRSADec.Location = new System.Drawing.Point(108, 58);
            this.btnRSADec.Size = new System.Drawing.Size(90, 26);
            this.btnRSADec.Click += new System.EventHandler(this.btnRSADec_Click);
            this.btnRSADec.TabIndex = 11;

            this.btnRSAClear.Text = "Xoá";
            this.btnRSAClear.Location = new System.Drawing.Point(206, 58);
            this.btnRSAClear.Size = new System.Drawing.Size(70, 26);
            this.btnRSAClear.Click += new System.EventHandler(this.btnRSAClear_Click);
            this.btnRSAClear.TabIndex = 12;

            this.lblRSAFormula.Text = "Công thức và kết quả:";
            this.lblRSAFormula.Location = new System.Drawing.Point(10, 98);
            this.lblRSAFormula.Size = new System.Drawing.Size(300, 16);

            this.txtRSAResult.Location = new System.Drawing.Point(10, 116);
            this.txtRSAResult.Size = new System.Drawing.Size(624, 112);
            this.txtRSAResult.Multiline = true;
            this.txtRSAResult.ReadOnly = true;
            this.txtRSAResult.Font = new System.Drawing.Font("Courier New", 10f);
            this.txtRSAResult.BackColor = System.Drawing.SystemColors.Control;
            this.txtRSAResult.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtRSAResult.TabStop = false;
            this.txtRSAResult.TabIndex = 13;

            // ── Form ─────────────────────────────────────────────────
            this.AutoScaleDimensions = new System.Drawing.SizeF(7f, 15f);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(682, 498);
            this.Controls.Add(this.tabControl1);
            this.Font = new System.Drawing.Font("Segoe UI", 9f);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "CipherLab — PlayFair & RSA";

            // Resume layouts
            this.grpRSAEnc.ResumeLayout(false);
            this.grpRSAKey.ResumeLayout(false);
            this.tabRSA.ResumeLayout(false);
            this.grpPFInput.ResumeLayout(false);
            this.grpPFKey.ResumeLayout(false);
            this.tabPlayFair.ResumeLayout(false);
            this.tabControl1.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();
        }

        #endregion

        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPlayFair;
        private System.Windows.Forms.TabPage tabRSA;

        private System.Windows.Forms.GroupBox grpPFKey;
        private System.Windows.Forms.Label lblPFKey;
        private System.Windows.Forms.TextBox txtPFKey;
        private System.Windows.Forms.Label lblPFMatrix;
        private System.Windows.Forms.TextBox txtPFMatrix;

        private System.Windows.Forms.GroupBox grpPFInput;
        private System.Windows.Forms.Label lblPFPlain;
        private System.Windows.Forms.TextBox txtPFPlain;
        private System.Windows.Forms.Label lblPFPrepared;
        private System.Windows.Forms.TextBox txtPFPrepared;
        private System.Windows.Forms.Label lblPFCipher;
        private System.Windows.Forms.TextBox txtPFCipher;
        private System.Windows.Forms.Button btnPFEncrypt;
        private System.Windows.Forms.Button btnPFDecrypt;
        private System.Windows.Forms.Button btnPFClear;

        private System.Windows.Forms.GroupBox grpRSAKey;
        private System.Windows.Forms.Label lblRSAP;
        private System.Windows.Forms.TextBox txtRSAP;
        private System.Windows.Forms.Label lblRSAQ;
        private System.Windows.Forms.TextBox txtRSAQ;
        private System.Windows.Forms.Button btnRSAGen;
        private System.Windows.Forms.Label lblRSAN;
        private System.Windows.Forms.TextBox txtRSAN;
        private System.Windows.Forms.Label lblRSAPhi;
        private System.Windows.Forms.TextBox txtRSAPhi;
        private System.Windows.Forms.Label lblRSAE;
        private System.Windows.Forms.TextBox txtRSAE;
        private System.Windows.Forms.Label lblRSAD;
        private System.Windows.Forms.TextBox txtRSAD;
        private System.Windows.Forms.Label lblRSAKeyNote;

        private System.Windows.Forms.GroupBox grpRSAEnc;
        private System.Windows.Forms.Label lblRSAM;
        private System.Windows.Forms.TextBox txtRSAM;
        private System.Windows.Forms.Label lblRSAC;
        private System.Windows.Forms.TextBox txtRSAC;
        private System.Windows.Forms.Button btnRSAEnc;
        private System.Windows.Forms.Button btnRSADec;
        private System.Windows.Forms.Button btnRSAClear;
        private System.Windows.Forms.Label lblRSAFormula;
        private System.Windows.Forms.TextBox txtRSAResult;

        private System.Windows.Forms.ToolTip toolTip1;
    }
}

