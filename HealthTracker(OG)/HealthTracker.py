import tkinter as tk
from tkinter import ttk 
import requests
import csv
from datetime import date
import os.path
from os import path

#Calculate the current day
today = date.today()
d1 = today.strftime("%m/%d/%Y")
#List of all the CSV files and the rows
filenames_list={"CaloriesIntake.csv":['Date','Item','Calories','Fat','Carbs','Fiber','Protein'] ,"First_Survey.csv":  ['Name','Gender','Age','Height (m)','Weight (Kg)','Goal','Goal Weight','Deadline(Week)'],\
"Weight_Tracker.csv" : ["Height","Weight","BMI","Date"],"Water.csv":["Date","Amount(oz)"]}
#Adding a row to a CSV file
def adding_Csv(filename,File_Row):
                with open(filename,'a+',newline='') as csvfile:
                    csvwrite=csv.writer(csvfile)
                    csvwrite.writerow(File_Row)

#Start each Frame
def start(self,parent,controller):
    tk.Frame.__init__(self,parent)
    self.configure(background="white")
    self.controller=controller
    self.s=ttk.Style()

def create_Csv():
                for filename,fields in filenames_list.items():
                    with open(filename,'w',newline='') as csvfile:
                        csvwrite=csv.writer(csvfile)
                        csvwrite.writerow(fields)

def clear_label(master,row,column,color):
    ttk.Label(master=master,text="                                                                           ",background=color).grid(row=row,column=column)
class App_HEHE(tk.Tk):
    def __init__(self, *args, **kwargs):
        tk.Tk.__init__(self, *args, **kwargs)
        tk.Tk.iconbitmap(self,default="icon.ico")
        container = tk.Frame(self)
        container.pack(side="top", fill="both", expand=True)
        container.grid_rowconfigure(0, weight=1)
        container.grid_columnconfigure(0, weight=1)
        
        self.s=ttk.Style()
        self.s.theme_use('clam')
        self.Overall_Style=ttk.Style()
        self.Overall_Style.configure('Overall.TButton',background='#369CE1',foreground='white',borderwidth=1)
        self.Overall_Style.map("Overall.TButton",foreground=[('pressed', '!disabled','black'),('active','black')],background=[('pressed', '!disabled', 'light green'),('active','light green')])
        self.frames = {}
        
        for F,geometry in zip((StartPage, CaloriesCounter, User_Survey,Water_Tracker), ('400x200', '575x400', '390x350','500x500')):
            page_name = F.__name__
            frame = F(parent=container, controller=self)
            self.frames[page_name] = (frame, geometry)
            frame.grid(row=0, column=0, sticky="nsew")
            
        self.show_frame("StartPage")

    def show_frame(self, page_name):
        '''Show a frame for the given page name'''
        frame, geometry = self.frames[page_name]
        # change geometry of the window
        self.update_idletasks()
        self.geometry(geometry)
        frame.tkraise()        

        
class StartPage(ttk.Frame):


    def __init__(self, parent, controller):
        #What will be display when it's the user's first time using
        def first_Time():
            ttk.Label(self,text="Hello! It seems that you are new!",background="white").pack()
            ttk.Label(self,text="Please Press CSV File",background="white").pack()
            ttk.Label(self,text="After you finish the survey, the app closed",background="white").pack()
            ttk.Label(self,text="Reopen to reuse.",background="white").pack()
            Button_CSV= ttk.Button(self,text='CSV File', command= lambda:run_firsttime(),style='Overall.TButton')
            Button_CSV.pack()
        def run_firsttime():
                create_Csv()
                controller.show_frame("User_Survey")

        start(self,parent,controller)
        if (path.exists("First_Survey.csv")== True):
            with open("First_Survey.csv") as csv_file:
                csv_reader = csv.reader(csv_file, delimiter=',')
                line_count=0
                for row in csv_reader:
                    if line_count ==0:
                        line_count +=1
                        
                        continue
                    else:
                        line_count +=1
                        
                        continue
                if line_count==1:
                    first_Time()
                else:
                    #what will be display after multiple time used
                    ttk.Label(self,text="Welcome Back " + row[0] +". Let's Have a Great Day!",background="white").pack()
                    button = ttk.Button(self, text="Calories Counter",
                        command=lambda: controller.show_frame("CaloriesCounter"),style='Overall.TButton')
                    button.pack()
                    button = ttk.Button(self, text="Water Tracker",
                        command=lambda: controller.show_frame("Water_Tracker"),style='Overall.TButton')
                    button.pack()

        else:
            first_Time()


class CaloriesCounter(ttk.Frame):

    def __init__(self, parent, controller):
        start(self,parent,controller) 
        self.configure(background="#e1ffda")    
        def BSR_Calculate():
            Gender=""
            Age=0.0
            Weight=0.0
            Height=0.0
            with open("First_Survey.csv") as csvfile:
                csv_reader = csv.reader(csvfile, delimiter=',')
                line_count=0
                for row in csv_reader:
                    if line_count ==0:
                        line_count +=1
                        continue
                    else:
                        Gender=row[1]
                        Age=float(row[2])
                        Goal_Weight=row[6]
                        Week=row[7]
            with open("Weight_Tracker.csv") as csvfile:
                csv_reader = csv.reader(csvfile,delimiter=',')
                line_count=0
                for row in csv_reader:
                    if line_count==0:
                        line_count +=1
                        continue
                    else:
                        Height=float(row[0])
                        Weight=float(row[1])
            if Gender=="Male":
                BSR=66.47+ (13.7 * Weight)+(5* Height*100.0)-(6.8*Age)
            elif Gender=="Female":
                BSR=655.1+(9.6* Weight)+(1.8*Height*100)-(4.7*Age)
            Calo=BSR*1.375
            if float(Week)>0:
                CaloriesDeficit=float(Goal_Weight)/float(Week) *500
                return (Calo-CaloriesDeficit)
            else:
                return Calo


        filename = "CaloriesIntake.csv"
        name=tk.StringVar()
        Caloriez=[d1,0.0,0.0,0.0,0.0,0.0,0.0]
        DailyAmount_Calories=[]
        Daily_Calories=0
        if (path.exists("First_Survey.csv")== True):
            with open("First_Survey.csv") as csv_file:
                csv_reader = csv.reader(csv_file, delimiter=',')
                line_count=0
                for row in csv_reader:
                    if line_count ==0:
                        line_count +=1
                        
                        continue
                    else:
                        line_count +=1
                        
                        continue
                if line_count>1:
                    BSR=BSR_Calculate()
                    BMR_Label=tk.Label(self,text="You should eat around "+ str(BSR)+" calories today!",background="#e1ffda").grid(row=1,column=1)
        
        def run():
            
             setting3=name.get()
             Entry_URL.delete(0,tk.END)
             tk.Label(text="                                                                                                          ",master=self,background="#e1ffda").grid(column=1,row=13)
             r=requests.get(setting3)
             from bs4 import BeautifulSoup
             soup=BeautifulSoup(r.text,'html.parser')
            
             Calories_z=soup.find_all('h2',attrs={'class':'MuiTypography-root MuiCardHeader-title MuiTypography-h4 MuiTypography-colorInherit MuiTypography-gutterBottom MuiTypography-displayBlock'})
             Caloriez[2]=Calories_z[0].text.replace(" Calories","")
             String_Calories="The Calories of this Item is : " + str(Caloriez[2])
             
             Macro=soup.find_all('td',attrs={'class':'MuiTableCell-root jss383 MuiTableCell-body MuiTableCell-alignCenter'})
             Caloriez[3]=Macro[0].text.replace(" g","")
             Caloriez[4]=Macro[1].text.replace(" g","")
             Caloriez[5]=Macro[2].text.replace(" g","")
             Caloriez[6]=Macro[3].text.replace(" g","")
            
             meal=soup.find_all('h1',attrs={'class':'MuiTypography-root MuiTypography-h4'})
             Caloriez[1]=(meal[0].text.replace("How many calories in",""))
             Calo_Label=tk.Label(text=Caloriez[1],master=self,background="#e1ffda").grid(column=1,row=13)
             Meal_Label=tk.Label(text=String_Calories,master=self,background="#e1ffda").grid(column=1,row=14)

             adding_Csv(filename,Caloriez)
             calculating_Calories()
        def calculating_Calories():
                with open(filename) as csvfile:
                    csv_reader = csv.reader(csvfile, delimiter=',')
                    line_count=0
                    for row in csv_reader:
                        if line_count ==0:
                            line_count +=1
                            continue
                        else:
                            if row[0] ==d1:
                                DailyAmount_Calories.append(float(row[2]))
                                line_count +=1
                Daily_Calories=sum(DailyAmount_Calories)
                String_Calories_Intake="The Amount of Calories You ate Today is: " + str(Daily_Calories)
                tk.Label(text=String_Calories_Intake,master=self,background="#e1ffda").grid(column=1,row=15  )
        def dont():
            tk.Label(text="                                                                                                          ",master=self,background="#e1ffda").grid(column=1,row=13)
            for i in range(len(List_Manual_Entry_Name)+1):
                if i==1:
                    Caloriez[i]=List_Manual_Entry_Name[i-1].get()
                elif i>1:
                    if(List_Manual_Entry_Name[i-1].get()==''):
                        Caloriez[1]==0
                    else:
                        Caloriez[i]=float(List_Manual_Entry_Name[i-1].get())
            String_Calories="The Calories of this Item is : " + str(Caloriez[2])
            Calo_Label=tk.Label(text=Caloriez[1],master=self,background="#e1ffda").grid(column=1,row=13)
            Meal_Label=tk.Label(text=String_Calories,master=self,background="#e1ffda").grid(column=1,row=14)

            adding_Csv(filename,Caloriez)
            calculating_Calories()



                
        Instruction_URL=tk.Label(self,text="Input the Website URL:",background='#e1ffda')
        Instruction_URL.grid(row=3, column=0)
            
        Button_URL= ttk.Button(self,text='Submit',command=run,style='Overall.TButton')
        Button_URL.grid(row=3,column=2)
 
        Instruction_Url=tk.Label(self,text="Please input all you know",background="#e1ffda")
        Instruction_Url.grid(row=4,column=1)
        ListofEntry=[]
        List_Manual_Entry_Name=[tk.StringVar(),tk.StringVar(),tk.StringVar(),tk.StringVar(),tk.StringVar(),tk.StringVar()]
        counter=0
        linecount=5
        skip=False
        for items in filenames_list["CaloriesIntake.csv"]:
            
            if items=="Date":
                skip=True
            if skip:
                skip=False
            else:
                tk.Label(self,text=items+": ",background="#e1ffda").grid(row=linecount,column=0)
                Entry=tk.Entry(self,textvariable=List_Manual_Entry_Name[counter],width=50).grid(row=linecount,column=1)
                ListofEntry.append(Entry)
                linecount+=1
                counter+=1
        ttk.Button(self, text='Submit',command=lambda: dont(),style='Overall.TButton').grid(row=12,column=1)
        

        S_Date="Today Date is: " + d1
        TDate=tk.Label(self,text=S_Date,background="#e1ffda")
        TDate.grid(row=0,column=1)
        tk.Label(self,text='Either input URL website or Manually input everything you know',background='#e1ffda').grid(row=2,column=1)
        
        Entry_URL=tk.Entry(self,textvariable=name,width=50)
        Entry_URL.grid(row=3, column=1)

        start_Page = ttk.Button(self, text="Back to Home",
                            command=lambda: controller.show_frame("StartPage"),style='Overall.TButton')
        start_Page.grid(row=16,column=1)
class Water_Tracker(ttk.Frame):
    def __init__(self,parent,controller):
        start(self,parent,controller) 
        self.configure(background='beige')
        def water(amount):
            Water[1]=amount
            adding_Csv('Water.csv',Water)
            
        Water=[d1,0.0]    
        Label=ttk.Label(self,text="Water Tracker",background="beige").grid(row=0,column=1)
        Weight=0
        if (path.exists("First_Survey.csv")== True):
            with open("First_Survey.csv") as csv_file:
                csv_reader = csv.reader(csv_file, delimiter=',')
                line_count=0
                for row in csv_reader:
                    if line_count ==0:
                        line_count +=1
                        
                        continue
                    else:
                        Weight=row[4]
        Weight_Lb=float(Weight)*2.205
        Amount_Of_Water_Ounces=float("{:.0f}".format(Weight_Lb*(2/3)))
        ttk.Label(self,text="You should drink around "+str(Amount_Of_Water_Ounces) +" Onces per day (No exercise)",background='beige').grid(row=1,column=1)

        ttk.Label(self,text="Manual Input:",background="beige").grid(row=2,column=0)
        AmountWater=tk.StringVar()
        tk.Entry(self,textvariable=AmountWater,width=50).grid(row=2,column=1)
        Manual_Water_Button=ttk.Button(self,text='Submit',command= lambda: water(float(AmountWater.get())),style='Overall.TButton').grid(row=2,column=2)
        start_Page = ttk.Button(self, text="Back to Home",
                            command=lambda: controller.show_frame("StartPage"),style='Overall.TButton')
        start_Page.grid(row=16,column=1)


class User_Survey(ttk.Frame):

    def __init__(self, parent, controller):
        start(self,parent,controller)


        self.s.map("Gender_Male.TButton",foreground=[('pressed', '!disabled','black'),('active','black')],background=[('pressed', '!disabled', 'light green'),('active','light green')])
        self.s.configure("Gender_Male.TButton",background='#369CE1',foreground='white',borderwidth=0)
        self.s.map("Gender_Female.TButton",foreground=[('pressed', '!disabled','black'),('active','black')],background=[('pressed', '!disabled', 'light green'),('active','light green')])
        self.s.configure("Gender_Female.TButton",background='#369CE1',foreground='white',borderwidth=0)
       
        Weight_Input=tk.StringVar()
        Height_Input=tk.StringVar()
        Name_Input=tk.StringVar()
        Goal_Weight=tk.StringVar()
        Goal_Week=tk.StringVar()
        Age_Input=tk.StringVar()
        
        Even=[0]
        fields =['Name','Gender','Age','Height (m)','Weight (Kg)','Goal','Goal Weight','Deadline(Week)']
        filename = "First_Survey.csv"
        Data=['','',0,0.0,0.0,'',0.0,0]
        First_input=[0.0,0.0,0.0,d1]
        def GoalFunction(event):
            User_goal=Goal_Choice.get()
            global Weight_Goal_Entry
            global Week_Goal_Entry
            global week_goal_label
            global weight_goal_label
            Data[5]=User_goal
            if User_goal=="Lose Weight":
                weight_goal_label=tk.Label(self,text="Goal Weight:",background="white")
                weight_goal_label.grid(row=8,column=0)
                Weight_Goal_Entry=tk.Entry(self,textvariable=Goal_Weight,width=5,background="yellow")
                Weight_Goal_Entry.grid(row=8,column=1,sticky="w")
                week_goal_label=tk.Label(self,text="How Many Weeks:",background="white")
                week_goal_label.grid(row=8,column=1,sticky="e")
                Week_Goal_Entry=tk.Entry(self,textvariable=Goal_Week,width=5,background="yellow")
                Week_Goal_Entry.grid(row=8,column=2)
                Even[0]=1
            elif User_goal=="Same Weight":
                if Even[0]==1:
                   Weight_Goal_Entry.destroy()
                   Week_Goal_Entry.destroy()
                   weight_goal_label.destroy()
                   week_goal_label.destroy()
                Even[0]=0
            if event=="Hi":
                Weight_Goal_Entry.destroy()
                Week_Goal_Entry.destroy()
                weight_goal_label.destroy()
                week_goal_label.destroy()               


        def run():
            User_goal=Goal_Choice.get()
            User_Weight=float(Weight_Input.get())
            User_Height=float(Height_Input.get())
            User_Name=str(Name_Input.get())
            Data[2]=float(Age_Input.get())
            Data[0]=User_Name
            if User_goal=="Lose Weight":
                Data[6]=float(Goal_Weight.get())
                Data[7]=float(Goal_Week.get())
                if (User_Weight-float(Goal_Weight.get()))/float(Goal_Week.get())>2:
                    ttk.Label(self,text="It is not safe to lose more than 2lbs a week!!",background="white",foreground='red').grid(row=14,column=1)
            else:
                Data[6]=0
                Data[7]=0
            #Metrics
            if User_Height<4:
                Total=float("{:.2f}".format((User_Weight)/((User_Height)**2)))
                Data[3]=float("{:.2f}".format(User_Height))
                Data[4]=float("{:.2f}".format(User_Weight))
            #Imperials
            else:
                Total=float("{:.2f}".format((User_Weight)/((User_Height)**2)*703))
                Data[3]=float("{:.2f}".format(User_Height/39.37))
                Data[4]=float("{:.2f}".format(User_Weight/2.205))
            First_input[0]= Data[3]
            First_input[1]= Data[4]
            First_input[2]= Total  
            adding_Csv("Weight_Tracker.csv",First_input)
            adding_Csv(filename,Data)
            Entry_Height.delete(0,tk.END)
            Entry_Weight.delete(0,tk.END)
            Name_Entry.delete(0,tk.END)
            Age_Entry.delete(0,tk.END)
            Analyze_BMI(Total)
            tk.Label(text=("Your BMI is: "+str(Total)),master=self,background='white').grid(column=1,row=12)
        def Analyze_BMI(Total):
            if Total<18.5:
                tk.Label(text=("Underweight"),master=self,background='white').grid(column=1,row=13)
            elif Total>18.5 and Total<25:
                tk.Label(text=("Normal"),master=self,background='white').grid(column=1,row=13)
            elif Total>25 and Total<30:
                tk.Label(text=("Overweight"),master=self,background='white').grid(column=1,row=13)
            elif Total>30:
                tk.Label(text=("Obese"),master=self,background='white').grid(column=1,row=13)
        def gender(number):
            if number==1:
                Data[1]='Male'
                self.s.configure("Gender_Male.TButton",background="green",foreground="white")
                self.s.configure("Gender_Female.TButton",background="light gray",foreground="black")
            elif number==2:
                Data[1]='Female'
                self.s.configure("Gender_Female.TButton",background="green",foreground="white")
                self.s.configure("Gender_Male.TButton",background="light gray",foreground="black")
        def restart():
            create_Csv()
            self.s.map("Gender_Male.TButton",foreground=[('pressed', '!disabled','black'),('active','black')],background=[('pressed', '!disabled', 'light green'),('active','light green')])
            self.s.configure("Gender_Male.TButton",background='#369CE1',foreground='white',borderwidth=0)
            self.s.map("Gender_Female.TButton",foreground=[('pressed', '!disabled','black'),('active','black')],background=[('pressed', '!disabled', 'light green'),('active','light green')])
            self.s.configure("Gender_Female.TButton",background='#369CE1',foreground='white',borderwidth=0)
            for i in range(12,15):
                clear_label(self,i,1,"white")
            Goal_Choice.set(' ')
            GoalFunction("Hi")
                

        
        Title=tk.Label(self,text="Input your Statistics",background="white")
        Title.grid(row=0,column=1)

        Note=tk.Label(self,text="Keep units consistent",background="white")
        Note.grid(row=1,column=1)
        
        Name_Label=tk.Label(self,text="Name (First Last): ",background="white")
        Name_Label.grid(row=2,column=0)
        Name_Entry=tk.Entry(self,textvariable=Name_Input,width=30,background="yellow")
        Name_Entry.grid(row=2,column=1)

        Age_Label=tk.Label(self,text="Age: ",background="white")
        Age_Label.grid(row=3,column=0)
        Age_Entry=tk.Entry(self,textvariable=Age_Input,width=30,background="yellow")
        Age_Entry.grid(row=3,column=1)


        Weight=tk.Label(self,text="Weight (Kg/lbs): ",background="white")
        Weight.grid(row=4,column=0)
        Entry_Weight=tk.Entry(self,textvariable=Weight_Input,width=30,background="yellow")
        Entry_Weight.grid(row=4, column=1)
        
        
        Height=tk.Label(self,text="Height (m/in): ",background="white")
        Height.grid(row=5,column=0)
        Entry_Height=tk.Entry(self,textvariable=Height_Input,width=30,background="yellow")
        Entry_Height.grid(row=5, column=1)

        Gender_Label=tk.Label(self,text="Gender: ",background="white")
        Gender_Label.grid(row=6,column=0)
        Male_Button=ttk.Button(self,text="Male",command= lambda:gender(1),style='Gender_Male.TButton')
        Male_Button.grid(row=6,column=1,stick="e")
        Female_Button=ttk.Button(self,text="Female",command= lambda:gender(2),style="Gender_Female.TButton")
        Female_Button.grid(row=6,column=1,stick="w")
        
        ttk.Label(self,text="What is your goal:",background="white").grid(row=6,column=0)
        Goal_Choice=ttk.Combobox(self,values=["Same Weight","Lose Weight"],background="yellow",state="readonly")
        Goal_Choice.grid(row=7,column=1)
        Goal_Choice.bind("<<ComboboxSelected>>",GoalFunction)
        Button_Submit= ttk.Button(self,text='Submit',command=run,style='Overall.TButton')
        Button_Submit.grid(row=9,column=1)

        ttk.Button(self,text='Restart',command=lambda: restart(),style='Overall.TButton').grid(row=11,column=1)
        start_Page = ttk.Button(self, text="Close the App",
                            command=lambda:controller.destroy(),style='Overall.TButton')
        start_Page.grid(row=10,column=1)


if __name__ == "__main__":
    app = App_HEHE()
    app.resizable(False, False)
    app.title("Your Fitness")
    app.mainloop()
