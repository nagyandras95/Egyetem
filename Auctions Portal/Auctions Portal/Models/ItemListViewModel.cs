using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Auctions_Portal.Models
{
    public class ItemListViewModel
    {

        public List<Item> ListedItems { get; set; }

        public FilterViewModel Filter { get; set; }

        public Int32? Category { get; set; }

        public Int32 ScrollIndex { get; set; }

        public Int32 HowMany { get; set; }

        //Filter
        public String ItemName { get; set; }


    }
}