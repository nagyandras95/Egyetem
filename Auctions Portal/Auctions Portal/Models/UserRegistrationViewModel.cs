using System;
using System.ComponentModel.DataAnnotations;
using System.Web.Mvc;

namespace Auctions_Portal.Models
{
    /// <summary>
    /// Datas of new user
    /// </summary>
    public class UserRegistrationViewModel
    {
        [HiddenInput(DisplayValue = false)]
        public Int32 UserId { get; set; }

        /// <summary>
        /// User's name.
        /// </summary>
        [Required(ErrorMessage ="Teljes név megadása köteléeztő.")]
        public String OriginalName { get; set; }

        /// <summary>
        /// User's user name wich is neccessary for login
        /// </summary>
       [Required(ErrorMessage ="Felhasználónév megadása köteléeztő.")]
        public String UserName { get; set; }

        /// <summary>
        /// User's password
        /// </summary>
        [DataType(DataType.Password)]
        [UIHint("Password")]
        [Required(ErrorMessage = "Jelszó megadása kötelező.")]
        public String Password { get; set; }

        [UIHint("Password")]
        [DataType(DataType.Password)]
        [Required(ErrorMessage = "Jelszó megerősítés megadása köteléeztő.")]
        public String ConfirmPassword { get; set; }

        /// <summary>
        /// User's phone number
        /// </summary>

        [DataType(DataType.PhoneNumber)]
        [Required(ErrorMessage = "Telefonszám megadása kötelező.")]
        public String PhoneNumber { get; set; }

        /// <summary>
        /// User's e-mail adress
        /// </summary>
        [DataType(DataType.EmailAddress)]
        [Required(ErrorMessage = "E-mail cím megadása köteléeztő.")]
        [EmailAddress(ErrorMessage="Az e-mail cím nem megfelelő formátumú.")]
        public String EmailAdress { get; set; }
        
    }
}