using System;
//using Microsoft.AspNet.Identity.EntityFramework;

namespace Auctions_Portal.Models
{
    public class IdentityGuest //: IdentityUser
    {

        /// <summary>
        /// Teljes név.
        /// </summary>
        public String Name { get; set; }

        /// <summary>
        /// Cím.
        /// </summary>
        public String Address { get; set; }
    }
}