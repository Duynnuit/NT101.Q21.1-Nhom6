using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace CipherProject_NT101
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
            PF_ShowMatrix();
        }

        // ══════════════════════════════════════════════════════════════
        //  PLAYFAIR
        // ══════════════════════════════════════════════════════════════
        private char[,] _pfMat = new char[5, 5];
        private Dictionary<char, (int r, int c)> _pfPos = new Dictionary<char, (int, int)>();

        private void PF_BuildMatrix(string key)
        {
            key = key.ToUpper().Replace("J", "I");
            bool[] used = new bool[26];
            used['J' - 'A'] = true;

            var order = new List<char>();
            foreach (char c in key)
                if (c >= 'A' && c <= 'Z' && !used[c - 'A'])
                { order.Add(c); used[c - 'A'] = true; }

            for (char c = 'A'; c <= 'Z'; c++)
                if (!used[c - 'A']) order.Add(c);

            _pfPos.Clear();
            for (int i = 0; i < 25; i++)
            {
                _pfMat[i / 5, i % 5] = order[i];
                _pfPos[order[i]] = (i / 5, i % 5);
            }
        }

        private void PF_ShowMatrix()
        {
            string key = txtPFKey.Text.Trim();
            if (key.Length == 0) key = "KEYWORD";
            PF_BuildMatrix(key);

            var sb = new StringBuilder();
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 5; j++)
                    sb.Append(_pfMat[i, j]).Append("  ");
                if (i < 4) sb.AppendLine();
            }
            txtPFMatrix.Text = sb.ToString();
        }

        private string PF_Prepare(string text)
        {
            text = text.ToUpper().Replace("J", "I");
            var clean = new StringBuilder();
            foreach (char c in text)
                if (c >= 'A' && c <= 'Z') clean.Append(c);

            var result = new StringBuilder();
            int idx = 0;
            while (idx < clean.Length)
            {
                result.Append(clean[idx]);
                if (idx + 1 < clean.Length)
                {
                    if (clean[idx] == clean[idx + 1]) { result.Append('X'); idx++; }
                    else { result.Append(clean[idx + 1]); idx += 2; }
                }
                else { result.Append('X'); idx++; }
            }
            return result.ToString();
        }

        private (char, char) PF_EncPair(char a, char b)
        {
            var (ra, ca) = _pfPos[a];
            var (rb, cb) = _pfPos[b];
            if (ra == rb) return (_pfMat[ra, (ca + 1) % 5], _pfMat[rb, (cb + 1) % 5]);
            if (ca == cb) return (_pfMat[(ra + 1) % 5, ca], _pfMat[(rb + 1) % 5, cb]);
            return (_pfMat[ra, cb], _pfMat[rb, ca]);
        }

        private (char, char) PF_DecPair(char a, char b)
        {
            var (ra, ca) = _pfPos[a];
            var (rb, cb) = _pfPos[b];
            if (ra == rb) return (_pfMat[ra, (ca + 4) % 5], _pfMat[rb, (cb + 4) % 5]);
            if (ca == cb) return (_pfMat[(ra + 4) % 5, ca], _pfMat[(rb + 4) % 5, cb]);
            return (_pfMat[ra, cb], _pfMat[rb, ca]);
        }

        private void txtPFKey_TextChanged(object sender, EventArgs e)
        {
            PF_ShowMatrix();
        }

        private void btnPFEncrypt_Click(object sender, EventArgs e)
        {
            try
            {
                PF_BuildMatrix(txtPFKey.Text);
                string prep = PF_Prepare(txtPFPlain.Text);
                if (prep.Length == 0)
                {
                    MessageBox.Show("Vui lòng nhập bản rõ!", "Thiếu dữ liệu",
                                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }

                var dg = new StringBuilder();
                for (int i = 0; i < prep.Length; i += 2)
                    dg.Append(prep[i]).Append(prep[i + 1]).Append(' ');
                txtPFPrepared.Text = dg.ToString().Trim();

                var cipher = new StringBuilder();
                for (int i = 0; i < prep.Length; i += 2)
                {
                    var (c1, c2) = PF_EncPair(prep[i], prep[i + 1]);
                    cipher.Append(c1).Append(c2);
                }

                txtPFCipher.Text =
                    "[MÃ HOÁ]\r\n" +
                    "Khoá    : " + txtPFKey.Text.ToUpper() + "\r\n" +
                    "Bản rõ  : " + txtPFPlain.Text.Trim().ToUpper() + "\r\n" +
                    "Digrams : " + dg.ToString().Trim() + "\r\n" +
                    "Bản mã  : " + cipher.ToString();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Lỗi: " + ex.Message, "Lỗi",
                                MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btnPFDecrypt_Click(object sender, EventArgs e)
        {
            try
            {
                PF_BuildMatrix(txtPFKey.Text);

                var clean = new StringBuilder();
                foreach (char c in txtPFPlain.Text.ToUpper())
                    if (c >= 'A' && c <= 'Z') clean.Append(c);
                string text = clean.ToString();

                if (text.Length == 0 || text.Length % 2 != 0)
                {
                    MessageBox.Show("Bản mã phải là chữ cái và có số ký tự chẵn!",
                                    "Dữ liệu không hợp lệ",
                                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }

                txtPFPrepared.Text = "(giải mã — không cần bước chuẩn bị)";

                var plain = new StringBuilder();
                for (int i = 0; i < text.Length; i += 2)
                {
                    var (c1, c2) = PF_DecPair(text[i], text[i + 1]);
                    plain.Append(c1).Append(c2);
                }

                txtPFCipher.Text =
                    "[GIẢI MÃ]\r\n" +
                    "Khoá    : " + txtPFKey.Text.ToUpper() + "\r\n" +
                    "Bản mã  : " + text + "\r\n" +
                    "Bản rõ  : " + plain.ToString();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Lỗi: " + ex.Message, "Lỗi",
                                MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btnPFClear_Click(object sender, EventArgs e)
        {
            txtPFPlain.Clear();
            txtPFPrepared.Clear();
            txtPFCipher.Clear();
        }

        // ══════════════════════════════════════════════════════════════
        //  RSA
        // ══════════════════════════════════════════════════════════════
        private long _rsaN, _rsaE, _rsaD;
        private bool _keysReady = false;

        private bool IsPrime(long n)
        {
            if (n < 2) return false;
            for (long i = 2; i * i <= n; i++)
                if (n % i == 0) return false;
            return true;
        }

        private long GCD(long a, long b) => b == 0 ? a : GCD(b, a % b);

        private long ModInverse(long a, long m)
        {
            long g0 = a, x0 = 1, g = m, x = 0;
            while (g > 0)
            {
                long q = g0 / g;
                long tmpG = g; g = g0 - q * g; g0 = tmpG;
                long tmpX = x; x = x0 - q * x; x0 = tmpX;
            }
            return (x0 % m + m) % m;
        }

        private long ModPow(long baseV, long exp, long mod)
        {
            long result = 1;
            baseV %= mod;
            while (exp > 0)
            {
                if ((exp & 1) == 1)
                    result = (long)((decimal)result * baseV % mod);
                baseV = (long)((decimal)baseV * baseV % mod);
                exp >>= 1;
            }
            return result;
        }

        private void btnRSAGen_Click(object sender, EventArgs e)
        {
            if (!long.TryParse(txtRSAP.Text.Trim(), out long p) ||
                !long.TryParse(txtRSAQ.Text.Trim(), out long q))
            {
                MessageBox.Show("p và q phải là số nguyên!", "Dữ liệu không hợp lệ",
                                MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            if (!IsPrime(p) || !IsPrime(q))
            {
                MessageBox.Show("p và q phải là số NGUYÊN TỐ!", "Dữ liệu không hợp lệ",
                                MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            if (p == q)
            {
                MessageBox.Show("p và q phải KHÁC NHAU!", "Dữ liệu không hợp lệ",
                                MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            _rsaN = p * q;
            long phi = (p - 1) * (q - 1);

            _rsaE = 65537;
            if (_rsaE >= phi) _rsaE = 3;
            while (GCD(_rsaE, phi) != 1) _rsaE += 2;
            _rsaD = ModInverse(_rsaE, phi);

            txtRSAN.Text = _rsaN.ToString();
            txtRSAPhi.Text = phi.ToString();
            txtRSAE.Text = _rsaE.ToString();
            txtRSAD.Text = _rsaD.ToString();
            _keysReady = true;

            MessageBox.Show(
                "Sinh khoá thành công!\r\n\r\n" +
                $"  Khoá công khai : (e = {_rsaE},  n = {_rsaN})\r\n" +
                $"  Khoá bí mật   : (d = {_rsaD},  n = {_rsaN})",
                "RSA — Sinh khoá", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void btnRSAEnc_Click(object sender, EventArgs e)
        {
            if (!_keysReady)
            {
                MessageBox.Show("Vui lòng sinh khoá trước!", "Chưa có khoá",
                                MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            if (!long.TryParse(txtRSAM.Text.Trim(), out long M) || M < 0)
            {
                MessageBox.Show("Bản rõ M phải là số nguyên không âm!", "Dữ liệu không hợp lệ",
                                MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            if (M >= _rsaN)
            {
                MessageBox.Show($"M phải nhỏ hơn n = {_rsaN}!", "Dữ liệu không hợp lệ",
                                MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            long C = ModPow(M, _rsaE, _rsaN);
            txtRSAC.Text = C.ToString();

            txtRSAResult.Text =
                "[MÃ HOÁ RSA]\r\n" +
                $"  Công thức : C = M^e mod n\r\n" +
                $"  Thay số   : C = {M}^{_rsaE} mod {_rsaN}\r\n" +
                $"  Kết quả   : C = {C}";
        }

        private void btnRSADec_Click(object sender, EventArgs e)
        {
            if (!_keysReady)
            {
                MessageBox.Show("Vui lòng sinh khoá trước!", "Chưa có khoá",
                                MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            if (!long.TryParse(txtRSAC.Text.Trim(), out long C) || C < 0)
            {
                MessageBox.Show("Bản mã C phải là số nguyên không âm!", "Dữ liệu không hợp lệ",
                                MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            long M = ModPow(C, _rsaD, _rsaN);
            txtRSAM.Text = M.ToString();

            txtRSAResult.Text =
                "[GIẢI MÃ RSA]\r\n" +
                $"  Công thức : M = C^d mod n\r\n" +
                $"  Thay số   : M = {C}^{_rsaD} mod {_rsaN}\r\n" +
                $"  Kết quả   : M = {M}";
        }

        private void btnRSAClear_Click(object sender, EventArgs e)
        {
            txtRSAM.Clear();
            txtRSAC.Clear();
            txtRSAResult.Clear();
        }
    }
}
