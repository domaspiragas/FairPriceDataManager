# FairPriceDataManager
A local data management application built for a small scale auto repair shop Fair Price Auto Repair

This is a project I architected and built in the Summer of 2016 for my father's business Fair Price Auto Repair. 

<h3>What Problem Does This Application Sovle?</h3>
Labor guides like Mitchell1's Ondemand5 cost a lot for extra features like historical quote preservation, and at the 
time of this project do not support unlimited historical records. The FairPriceDataManager allows you to save data related to
customers, their cars, and the jobs performed and has no limit to the number of records preserved. 

<h3>Some Feature Details</h3>

* Add/remove new customers and jobs with hotkey implementation
* Simplified process for adding jobs for existing customers
* New customer/job dialogs autoformat input so dates and phone numbers are stored with a consistent structure
* Sort by date or customer name
* Real-Time search by customer name
* Separate window listing all jobs for a specific customer
* Undo/Redo for adding/removing jobs and customers
* Local data storage datas treaming to a save file
* Save prompt on exit if unsaved changes exist
* Automatically generated backup save files with a simple way of restoring from backup saves

<h3>Other Details</h3>

* UI built in QTCreator which supports standard CSS
* Shippable executable with custom desktop and window icons
