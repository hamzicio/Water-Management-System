Public Class Form1

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click

        If My.Computer.Network.IsAvailable Then

            Dim programName As String = "Signup.exe"

            System.Diagnostics.Process.Start(Application.StartupPath & "\includes\" & programName)
        Else
            MessageBox.Show("Sorry, Internet Connection is not available. Please try again.", "No Internet Connection", MessageBoxButtons.OKCancel, MessageBoxIcon.Stop)

        End If

    End Sub

    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Timer1.Start()

        Label2.Text = Date.Now

    End Sub

    Private Sub Label1_Click(sender As Object, e As EventArgs) Handles Label1.Click

    End Sub

    Private Sub Button2_Click(sender As Object, e As EventArgs)

        If My.Computer.Network.IsAvailable Then

            Dim programName As String = "Add_Customer.exe"

            System.Diagnostics.Process.Start(Application.StartupPath & "\includes\" & programName)

        Else
            MessageBox.Show("Sorry, Internet Connection is not available. Please try again.", "No Internet Connection", MessageBoxButtons.OKCancel, MessageBoxIcon.Stop)

        End If

        
    End Sub

    Private Sub Button6_Click(sender As Object, e As EventArgs)

        If My.Computer.Network.IsAvailable Then
            Dim programName As String = "Show_orders.exe"

            System.Diagnostics.Process.Start(Application.StartupPath & "\includes\" & programName)
        Else
            MessageBox.Show("Sorry, Internet Connection is not available. Please try again.", "No Internet Connection", MessageBoxButtons.OKCancel, MessageBoxIcon.Stop)

        End If

        
    End Sub

    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick
        Label2.Text = Date.Now


    End Sub

    Private Sub Label3_Click(sender As Object, e As EventArgs) Handles Label3.Click

    End Sub

    Private Sub Button3_Click(sender As Object, e As EventArgs) Handles Button3.Click

        If My.Computer.Network.IsAvailable Then
            Dim programName As String = "Order.exe"

            System.Diagnostics.Process.Start(Application.StartupPath & "\includes\" & programName)
        Else
            MessageBox.Show("Sorry, Internet Connection is not available. Please try again.", "No Internet Connection", MessageBoxButtons.OKCancel, MessageBoxIcon.Stop)

        End If

       
    End Sub

    Private Sub Button4_Click(sender As Object, e As EventArgs)

        If My.Computer.Network.IsAvailable Then
            Dim programName As String = "Current_Record.exe"

            System.Diagnostics.Process.Start(Application.StartupPath & "\includes\" & programName)
        Else
            MessageBox.Show("Sorry, Internet Connection is not available. Please try again.", "No Internet Connection", MessageBoxButtons.OKCancel, MessageBoxIcon.Stop)

        End If


    End Sub

    Private Sub Button5_Click(sender As Object, e As EventArgs)

        If My.Computer.Network.IsAvailable Then
            Dim programName As String = "Old_Record.exe"

            System.Diagnostics.Process.Start(Application.StartupPath & "\includes\" & programName)
        Else
            MessageBox.Show("Sorry, Internet Connection is not available. Please try again.", "No Internet Connection", MessageBoxButtons.OKCancel, MessageBoxIcon.Stop)

        End If


    End Sub

    Private Sub Button7_Click(sender As Object, e As EventArgs)

        If My.Computer.Network.IsAvailable Then
            Dim programName As String = "Credentials.exe"

            System.Diagnostics.Process.Start(Application.StartupPath & "\includes\" & programName)
        Else
            MessageBox.Show("Sorry, Internet Connection is not available. Please try again.", "No Internet Connection", MessageBoxButtons.OKCancel, MessageBoxIcon.Stop)

        End If

        
    End Sub

    Private Sub Button4_Click_1(sender As Object, e As EventArgs) Handles Button4.Click
        If My.Computer.Network.IsAvailable Then
            Dim programName As String = "Profile.exe"

            System.Diagnostics.Process.Start(Application.StartupPath & "\includes\" & programName)
        Else
            MessageBox.Show("Sorry, Internet Connection is not available. Please try again.", "No Internet Connection", MessageBoxButtons.OKCancel, MessageBoxIcon.Stop)

        End If
    End Sub

    Private Sub Button2_Click_1(sender As Object, e As EventArgs) Handles Button2.Click
        If My.Computer.Network.IsAvailable Then
            Dim programName As String = "Records.exe"

            System.Diagnostics.Process.Start(Application.StartupPath & "\includes\" & programName)
        Else
            MessageBox.Show("Sorry, Internet Connection is not available. Please try again.", "No Internet Connection", MessageBoxButtons.OKCancel, MessageBoxIcon.Stop)

        End If
    End Sub
End Class
