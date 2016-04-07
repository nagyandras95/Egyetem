using System;
using System.ComponentModel.DataAnnotations;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Auctions_Portal.Models
{
    public class LoginViewModel
    {
        /// <summary>
        /// User's user name wich is neccessary for login
        /// </summary>
        [Required(ErrorMessage ="Hiányzik a felhasználó név!")]
        public String UserName { get; set; }

        /// <summary>
        /// User's password
        /// </summary>
        [DataType(DataType.Password)]
        [UIHint("Password")]
        [Required(ErrorMessage = "Hiányzik a jelszó!")]
        public String Password { get; set; }
    }
}