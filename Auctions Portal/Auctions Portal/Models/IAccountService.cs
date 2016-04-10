using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Auctions_Portal.Models
{
    public interface IAccountService
    {
        /// <summary>
        /// Get the number of users
        /// </summary>
        Int32 UserCount { get; }

        // <summary>
        /// Currently logged in user name.
        /// </summary>
        String CurrentUserName { get; }

        Users GetUser(String userName);
        /// <summary>
        /// Login user.
        /// </summary>
        /// <param name="user">The view model of the user</param>
        Boolean Login(LoginViewModel user);

        /// <summary>
        /// Logout user
        /// </summary>
        Boolean Logout();

        /// <summary>
        /// Registration of Guest
        /// </summary>
        /// <param name="guest">A vendég nézetmodellje.</param>
        Boolean Register(UserRegistrationViewModel user);

        

    }
}