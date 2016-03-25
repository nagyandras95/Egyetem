using System;
using System.ComponentModel.DataAnnotations;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Auctions_Portal.Models
{
    /// <summary>
    /// Datas of new user
    /// </summary>
    public class UserRegistrationViewModel
    {
        /// <summary>
        /// User's name.
        /// </summary>
        public String OriginalName { get; set; }

        /// <summary>
        /// User's user name wich is neccessary for login
        /// </summary>
        public String UserName { get; set; }

        /// <summary>
        /// User's password
        /// </summary>
        [DataType(DataType.Password)]
        public String Password { get; set; }

        [DataType(DataType.Password)]
        public String ConfirmPassword { get; set; }

        /// <summary>
        /// User's phone number
        /// </summary>

        [DataType(DataType.PhoneNumber)]
        public String PhoneNumber { get; set; }

        /// <summary>
        /// User's e-mail adress
        /// </summary>
        [DataType(DataType.EmailAddress)]
        public String EmailAdress { get; set; }
        
    }
}