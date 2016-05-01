using System;
using Microsoft.Win32;
using System.Windows;
using AuctionsPortal.Admin.View;
using AuctionsPortal.Admin.Model;
using AuctionsPortal.Admin.Persistence;
using AuctionsPortal.Admin.ViewModel;
using System.Windows;

namespace AuctionsPortal.Admin
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {

        private IAuctionsPortalModel _model;
        private LoginViewModel _loginViewModel;
        private LoginWindow _loginView;
        private MainViewModel _mainViewModel;
        private MainWindow _mainView;
        private ItemEditorVindow _editorView;

        public App()
        {
            Startup += new StartupEventHandler(App_Startup);
            Exit += new ExitEventHandler(App_Exit);
        }

        private void App_Startup(object sender, StartupEventArgs e)
        {
            _model = new AuctionsPortalModel(new AuctionPortalServicePersistence("http://localhost:19200/"));

            _mainViewModel = new MainViewModel(_model);
            _mainViewModel.MessageApplication += new EventHandler<MessageEventArgs>(ViewModel_MessageApplication);
            _mainViewModel.ItemEditingStarted += new EventHandler(MainViewModel_ItemEditingStarted);
            _mainViewModel.ItemEditingFinished += new EventHandler(MainViewModel_ItemEditingFinished);
            _mainViewModel.ImageEditingStarted += new EventHandler<ItemEventArgs>(MainViewModel_ImageEditingStarted);
            _mainViewModel.ExitApplication += new EventHandler(ViewModel_ExitApplication);
            _mainViewModel.Login += new EventHandler(ViewModel_Login);

            _mainView = new MainWindow();
            _mainView.DataContext = _mainViewModel;
            _mainView.Show();
        }

        public async void App_Exit(object sender, ExitEventArgs e)
        {
            if (_model.IsUserLoggedIn) // amennyiben be vagyunk jelentkezve, kijelentkezünk
            {
                await _model.LogoutAsync();
            }
        }

        private void ViewModel_LoginFailed(object sender, EventArgs e)
        {
            MessageBox.Show("A bejelentkezés sikertelen!", "Aukciós portál", MessageBoxButton.OK, MessageBoxImage.Asterisk);
        }

        private void ViewModel_LoginSuccess(object sender, EventArgs e)
        {

            _loginView.Close();
        }

        private void ViewModel_MessageApplication(object sender, MessageEventArgs e)
        {
            MessageBox.Show(e.Message, "Aukciós portál", MessageBoxButton.OK, MessageBoxImage.Asterisk);
        }

        private void MainViewModel_ItemEditingStarted(object sender, EventArgs e)
        {
            _editorView = new ItemEditorVindow(); // külön szerkesztő dialógus az épületekre
            _editorView.DataContext = _mainViewModel;
            _editorView.Show();
        }

        private void MainViewModel_ItemEditingFinished(object sender, EventArgs e)
        {
            _editorView.Close();
        }

        private void MainViewModel_ImageEditingStarted(object sender, ItemEventArgs e)
        {
            try
            {
                // egy dialógusablakban bekérjük a fájlnevet
                OpenFileDialog dialog = new OpenFileDialog();
                dialog.CheckFileExists = true;
                dialog.Filter = "Képfájlok|*.jpg;*.jpeg;*.bmp;*.tif;*.gif;*.png;";
                dialog.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.MyPictures);
                Boolean? result = dialog.ShowDialog();

                if (result == true)
                {
                    // kép létrehozása (a megfelelő méretekkel)
                    _model.CreateImage(e.ItemId,
                                       ImageHandler.OpenAndResize(dialog.FileName, 100));
                }
            }
            catch { }
        }



        private void ViewModel_ExitApplication(object sender, System.EventArgs e)
        {
            Shutdown();
        }

        private void ViewModel_Login(object sender, System.EventArgs e)
        {
            _loginViewModel = new LoginViewModel(_model);
            _loginViewModel.LoginSuccess += new EventHandler(ViewModel_LoginSuccess);
            _loginViewModel.LoginFailed += new EventHandler(ViewModel_LoginFailed);

            _loginView = new LoginWindow();
            _loginView.DataContext = _loginViewModel;
            _loginView.Show();
        }
    }
}
