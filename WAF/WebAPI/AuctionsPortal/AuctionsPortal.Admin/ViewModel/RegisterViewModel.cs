using System;
using System.Windows.Controls;
using AuctionsPortal.Admin.Model;
using AuctionsPortal.Data;
using AuctionsPortal.Admin.Persistence;

namespace AuctionsPortal.Admin.ViewModel
{
    public class RegisterViewModel : ViewModelBase
    {
        private IAuctionsPortalModel _model;

        public AdvatiserDTO AddedAdvatiser { get; set; }

        /// <summary>
        /// Kilépés parancsának lekérdezése.
        /// </summary>
        public DelegateCommand CanelCommand { get; private set; }

        /// <summary>
        /// Bejelentkezés parancs lekérdezése.
        /// </summary>
        public DelegateCommand RegisterCommand { get; private set; }

        public event EventHandler AddedAdvatiserStarted;

        public event EventHandler RegisterSucces;

        public event EventHandler RegisterFaild;

        public event EventHandler RegistrationEnd;

        /// <summary>
        /// Nézetmodell példányosítása.
        /// </summary>
        /// <param name="model">A modell.</param>
        public RegisterViewModel(IAuctionsPortalModel model)
        {
            if (model == null)
                throw new ArgumentNullException("model");

            _model = model;
            AddedAdvatiser = new AdvatiserDTO();

            CanelCommand = new DelegateCommand(param => OnCloseRegistartion());
            RegisterCommand = new DelegateCommand((param => RegisterAsync(param as PasswordBox)));


        }

        private async void RegisterAsync(PasswordBox passwordBox)
        {
            if (passwordBox == null)
                return;

            AddedAdvatiser.Password = passwordBox.Password;

            try
            {
                Boolean result = await _model.RegisterAsync(AddedAdvatiser);

                if (result)
                    OnRegisterSuccess();
                else
                    OnRegisterFailed();
            }
            catch (PersistenceUnavailableException)
            {
                OnMessageApplication("Nincs kapcsolat a kiszolgálóval.");
            }
        }

        private void OnRegisterSuccess()
        {
            if (RegisterSucces != null)
                RegisterSucces(this, EventArgs.Empty);
        }

        private void OnRegisterFailed()
        {
            if (RegisterFaild != null)
                RegisterFaild(this, EventArgs.Empty);
        }

        private void OnCloseRegistartion()
        {
            if (RegistrationEnd != null)
                RegistrationEnd(this, EventArgs.Empty);
        }
    }
}
