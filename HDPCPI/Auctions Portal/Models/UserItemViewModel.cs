using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Auctions_Portal.Models
{
    public class UserItemViewModel
    {
        public Item UserItem { get; set; }

        public Boolean First { get; set; }

        public Boolean Active { get; set;}

    }
}