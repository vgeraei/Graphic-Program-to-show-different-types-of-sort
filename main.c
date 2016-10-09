#include<stdlib.h>
#include <string.h>
#include <stdio.h>
#include "gtk/gtk.h"
#include "glib.h"
#include "glib-object.h"
#include "gio/gio.h"
#include "gdk/gdkkeysyms.h"
//buttons
GtkWidget *generate;
//sortwindow buttoms
GtkWidget *Print;
GtkWidget *BackwardShow;
GtkWidget *Previous;
GtkWidget *Next;
GtkWidget *ForwardShow;
/*Shared objects*/
GtkWidget *window;
GtkWidget *swindow;
GtkAccelGroup * accel_group;
GtkVBox * vbox;
GtkVBox * vboxbuttom;
GtkTextView * textview;
gchar path[256];
gboolean isChanged;
int counter;
char **firstdata;
char *data[100];
GtkWidget *entrygo;
GtkWidget *go;
gchar *entrygoamount;

//stack global
int now;
int all;
int *num;
int counter;
int i,j;
int toppu=0;
int toppo=0;
int n;
void swap();
struct step{
int from;
int to;
struct step *next;
};
typedef struct step step;
step *push;
step *pop;

//hadi prototypes
void wait(int z);  
void doo();
void undo();
void go_to (int n);




GtkWidget **labelshow;
GtkWidget *combobox;
	gchar *combo;
//label
void labelswap(GtkWidget **label1 , GtkWidget **label2);


/*Signal handlers*/
void fileNewMenuItemActivated(GtkWidget * widget, gpointer data);
void fileOpenMenuItemActivated(GtkWidget * widget, gpointer data);
void fileSaveMenuItemActivated(GtkWidget * widget, gpointer data);
void fileSaveAsMenuItemActivated(GtkWidget * widget, gpointer data);
void fileQuitMenuItemActivated(GtkWidget * widget, gpointer data);
void helpAboutMenuItemActivated(GtkWidget * widget, gpointer data);
void bufferChanged(GtkWidget * widget, gpointer data);
void fileRandomMenuItemActivated(GtkWidget * widget, gpointer data);
void GenerateItemActivated(GtkWidget * widget, gpointer data);
void OpenInNewWindow(GtkWidget *widget , gpointer data);
//sort prototypes
void swap(int *aptr,int *bptr); 
void bubblegen(int a[], int size);
void BubbleSort(GtkWidget * widget, gpointer data);
void SelectionSort(GtkWidget * widget, gpointer data);
void InsertionSort(GtkWidget * widget, gpointer data);
void QuickSort(GtkWidget * widget, gpointer data);
void BubbleSortD(GtkWidget * widget, gpointer data);
void SelectionSortD(GtkWidget * widget, gpointer data);
void InsertionSortD(GtkWidget * widget, gpointer data);
void QuickSortD(GtkWidget * widget, gpointer data);
void bubble_afza(int num[], int counter);
void quicksort(int array[] , int left , int right) ;
int partition(int array[] , int left , int right);
//sort buttons prototypes
void PrintFunc(GtkWidget * widget, gpointer data);
void BackwardShowFunc(GtkWidget * widget, gpointer data);
void PreviousFunc(GtkWidget * widget, gpointer data);
void NextFunc(GtkWidget * widget, gpointer data);
void ForwardShowFunc(GtkWidget * widget, gpointer data);
void Go(GtkWidget * widget, gpointer data);
/*Init graphics and connections*/
void initMenuBar();
void initToolBar();
void initTextEditor();

/*main function*/
int main(int argc, char *argv[])
{
	gtk_init(&argc,&argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"First Project");
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 500, 400);
	gtk_signal_connect(GTK_WINDOW(swindow),"clicked",G_CALLBACK(PrintFunc),NULL);
	gtk_signal_connect(GTK_WINDOW(swindow),"clicked",G_CALLBACK(BackwardShowFunc),NULL);
	gtk_signal_connect(GTK_WINDOW(swindow),"clicked",G_CALLBACK(PreviousFunc),NULL);
	gtk_signal_connect(GTK_WINDOW(swindow),"clicked",G_CALLBACK(NextFunc),NULL);
	gtk_signal_connect(GTK_WINDOW(swindow),"clicked",G_CALLBACK(ForwardShowFunc),NULL);
	gtk_signal_connect(GTK_WINDOW(swindow),"clicked",G_CALLBACK(Go),NULL);

    accel_group = gtk_accel_group_new();
	gtk_window_add_accel_group(GTK_WINDOW(window), accel_group);

	vbox = gtk_vbox_new(FALSE,3);
	vboxbuttom = gtk_vbox_new( FALSE , 3 ) ;
	gtk_container_add(GTK_WINDOW(window),vbox);
	gtk_widget_show(vbox);

	initMenuBar();
	initToolBar();
	initTextEditor();

	gtk_widget_show_all(window);



	gtk_main();
	return 0;
}

void initMenuBar()
{
		GtkMenuBar * menubar = gtk_menu_bar_new();
		gtk_box_pack_start(vbox,menubar,FALSE,FALSE,3);

		GtkMenuItem * fileMenuItem = gtk_menu_item_new_with_mnemonic("_File");
		gtk_menu_shell_append(menubar,fileMenuItem);

		GtkMenu * fileMenu = gtk_menu_new();
		gtk_menu_item_set_submenu(fileMenuItem,fileMenu);

		GtkImageMenuItem * fileNewMenuItem = gtk_image_menu_item_new_from_stock(GTK_STOCK_NEW,NULL);
		gtk_menu_shell_append(fileMenu,fileNewMenuItem);
		g_signal_connect(fileNewMenuItem,"activate",fileNewMenuItemActivated,NULL);

		GtkImageMenuItem * fileOpenMenuItem = gtk_image_menu_item_new_from_stock(GTK_STOCK_OPEN,NULL);
		gtk_menu_shell_append(fileMenu,fileOpenMenuItem);
		g_signal_connect(fileOpenMenuItem,"activate",fileOpenMenuItemActivated,NULL);
		
		GtkImageMenuItem * fileRandomMenuItem = gtk_image_menu_item_new_from_stock(GTK_STOCK_CONVERT,NULL);
        gtk_menu_shell_append(fileMenu,fileRandomMenuItem);
        g_signal_connect(fileRandomMenuItem,"activate",fileRandomMenuItemActivated,NULL);

		GtkMenuItem * sepItem = gtk_separator_menu_item_new();
		gtk_menu_shell_append(fileMenu,sepItem);

		GtkImageMenuItem * fileSaveMenuItem = gtk_image_menu_item_new_from_stock(GTK_STOCK_SAVE,NULL);
		gtk_menu_shell_append(fileMenu,fileSaveMenuItem);
		g_signal_connect(fileSaveMenuItem,"activate",fileSaveMenuItemActivated,NULL);

		GtkImageMenuItem * fileSaveAsMenuItem = gtk_image_menu_item_new_from_stock(GTK_STOCK_SAVE_AS,NULL);
		gtk_menu_shell_append(fileMenu,fileSaveAsMenuItem);
		g_signal_connect(fileSaveAsMenuItem,"activate",fileSaveAsMenuItemActivated,NULL);

		sepItem = gtk_separator_menu_item_new();
		gtk_menu_shell_append(fileMenu,sepItem);

		GtkImageMenuItem * fileQuitMenuItem = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT,accel_group);
		gtk_menu_shell_append(fileMenu,fileQuitMenuItem);
		g_signal_connect(fileQuitMenuItem,"activate",fileQuitMenuItemActivated,NULL);
		gtk_widget_add_accelerator(fileQuitMenuItem,"activate",accel_group,GDK_q,GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);

		GtkMenuItem * helpMenuItem = gtk_menu_item_new_with_mnemonic("_Help");
		gtk_menu_shell_append(menubar,helpMenuItem);

		GtkMenu * helpMenu = gtk_menu_new();
		gtk_menu_item_set_submenu(helpMenuItem,helpMenu);

		GtkMenuItem * helpAboutMenuItem = gtk_menu_item_new_with_mnemonic("_About");
		gtk_menu_shell_append(helpMenu,helpAboutMenuItem);
		g_signal_connect(helpAboutMenuItem,"activate",helpAboutMenuItemActivated,NULL);
}

void initToolBar()
{
	GtkToolbar * toolbar = gtk_toolbar_new();
	gtk_box_pack_start(vbox,toolbar,FALSE,FALSE,3);		
    
	GtkToolButton * toolbarSave = gtk_tool_button_new_from_stock(GTK_STOCK_NEW);
	gtk_toolbar_append_widget(toolbar,toolbarSave,"New","New file");
	g_signal_connect(toolbarSave,"clicked",fileNewMenuItemActivated,NULL);

	GtkToolButton * toolbarOpen = gtk_tool_button_new_from_stock(GTK_STOCK_OPEN);
	gtk_toolbar_append_widget(toolbar,toolbarOpen,"Open","Open file");
	g_signal_connect(toolbarOpen,"clicked",fileOpenMenuItemActivated,NULL);
	
	GtkToolButton * toolbarRandom = gtk_tool_button_new_from_stock(GTK_STOCK_CONVERT);
    gtk_toolbar_append_widget(toolbar,toolbarRandom,"Convert","Convert");
    g_signal_connect(toolbarRandom,"clicked",fileRandomMenuItemActivated,NULL);
    
    //seperator
    //gtk_toolbar_insert_space( toolbar, toolbarRandom );
    //buttom menu
   	//label
	GtkWidget *label = gtk_label_new( "        Type of sort : " );
    gtk_label_set_selectable (GTK_LABEL(label) , FALSE);	
	gtk_toolbar_append_widget(toolbar,label,"","");
	//combobox
	combobox = gtk_combo_new();
    GList *glist = NULL;
    glist = g_list_append (glist, "Bubble sort");
    glist = g_list_append (glist, "Bubble sort(Descending)");
    glist = g_list_append (glist, "Selection sort");
    glist = g_list_append (glist, "Selection sort(Descending)");
    glist = g_list_append (glist, "Insertion sort ");
    glist = g_list_append (glist, "Insertion sort (Descending)");
    glist = g_list_append (glist, "Quick sort");
    glist = g_list_append (glist, "Quick sort(Descending)");
    gtk_combo_set_popdown_strings (GTK_COMBO (combobox), glist);
    gtk_entry_set_text (GTK_ENTRY (GTK_COMBO (combobox)->entry), "Select the type of sort");
    gtk_toolbar_append_widget(toolbar,combobox,"","");
    g_free(glist);
	//Generate buttom
	generate = gtk_button_new_with_mnemonic ("_Generate");
	gtk_toolbar_append_widget(toolbar,generate,"","");
	gtk_signal_connect(GTK_WINDOW(generate),"clicked",G_CALLBACK(GenerateItemActivated),NULL);
    
}

void initTextEditor()
{
	textview = gtk_text_view_new();
	gtk_box_pack_start(vbox,textview,TRUE,TRUE,2);
	gtk_box_pack_start(vboxbuttom,textview,TRUE,TRUE,2);
	gtk_text_view_set_left_margin(textview,10);
	gtk_text_view_set_right_margin(textview,10);
	gtk_text_view_set_wrap_mode(textview,GTK_WRAP_WORD_CHAR);
	GtkTextBuffer *buffer = gtk_text_view_get_buffer(textview);
	g_signal_connect(buffer,"changed",bufferChanged,NULL);
	gtk_text_buffer_set_text(buffer,"",-1);
	strcpy(path,"");
	isChanged = FALSE;

}
void fileNewMenuItemActivated(GtkWidget * widget, gpointer data)
{
	if(isChanged)
	{
		GtkMessageDialog *mDialog = gtk_message_dialog_new(window,GTK_DIALOG_MODAL,GTK_MESSAGE_QUESTION,GTK_BUTTONS_YES_NO,"Do you want to save the current file?");
		gint res = gtk_dialog_run(mDialog);
		gtk_widget_destroy (mDialog);
		if(res == GTK_RESPONSE_YES)
			fileSaveMenuItemActivated(widget, data);
	}
	GtkTextBuffer *buffer = gtk_text_view_get_buffer(textview);
	gtk_text_buffer_set_text(buffer,"",-1);
	isChanged = FALSE;
	strcpy(path,"");
}


void fileOpenMenuItemActivated(GtkWidget * widget, gpointer data)
{
	GtkFileChooserDialog * fDialog = gtk_file_chooser_dialog_new("Choose file",window,GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL , GTK_RESPONSE_CANCEL,
    GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,NULL);
	gint res = gtk_dialog_run(fDialog);
	gchar * filename  = gtk_file_chooser_get_filename(fDialog);
	gtk_widget_destroy (fDialog);
	if(res != GTK_RESPONSE_ACCEPT)
		return;

	fileNewMenuItemActivated(widget,data);
	gchar * content;
	if(g_file_get_contents(filename,&content,NULL,NULL))
	{
		GtkTextBuffer *buffer = gtk_text_view_get_buffer(textview);
		gtk_text_buffer_set_text(buffer,content,-1);
		isChanged = FALSE;
		strcpy(path,filename);
        g_free(content);
	}
	else
	{
		GtkMessageDialog *mDialog = gtk_message_dialog_new(window,GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"File does not exist.");
		gtk_dialog_run(mDialog);
		gtk_widget_destroy (mDialog);
	}
    g_free(filename);
}

void fileRandomMenuItemActivated(GtkWidget *widget , gpointer data)
{
     GtkTextBuffer *buffer = gtk_text_view_get_buffer(textview);
    GtkTextIter start,end;
    gtk_text_buffer_get_start_iter(buffer , &start);
    gtk_text_buffer_get_end_iter(buffer , &end);
    gchar *contents = gtk_text_buffer_get_text(buffer, &start , &end , FALSE) ;
    counter = 1;
    int i;
	for( i=0;i<strlen(contents);i++)
		if(contents[i]==',')
			counter++;
    
    firstdata=malloc(counter* sizeof(char *));
    labelshow=malloc(counter* sizeof(GtkWidget));
	char *text=strtok(contents,",");

	i = 0;

	while(text!=NULL)
    {

		firstdata[i]=text;

		i++;

		text=strtok(NULL,",");

	}     
	    num = malloc(counter* sizeof(int));
    for(i=0 ; i<counter ; i++)
    {
            num[i] = firstdata[i];
            }
    static GtkWidget *swindow;
    GtkWidget *scrolled_window;
    GtkWidget *table;
    i=0;
    int j=0;
    int b;
    gtk_window_set_title (GTK_WINDOW (swindow), "Random");
    swindow = gtk_dialog_new ();
    gtk_container_set_border_width (GTK_CONTAINER (swindow), 0);
    gtk_widget_set_size_request (swindow, 550, 300);
    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 10);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	gtk_window_set_position(GTK_WINDOW(swindow), GTK_WIN_POS_CENTER);
	gtk_box_pack_start (GTK_BOX (GTK_DIALOG(swindow)->vbox), scrolled_window,TRUE, TRUE, 0);
	gtk_widget_show (scrolled_window);
	table = gtk_table_new (10, 10, FALSE);
	gtk_table_set_row_spacings (GTK_TABLE (table), 10);
    gtk_table_set_col_spacings (GTK_TABLE (table), 10);
    gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolled_window), table);
       i=0;
   j=0;
   

     gtk_widget_show (table);
     gtk_widget_show (swindow); 
         while(i<counter)
	{
                          b=i%10;
                          labelshow[i]=gtk_label_new(num[i]);
                          gtk_table_attach_defaults(GTK_TABLE (table), labelshow[i],b, b+1, j, j+1);
                          gtk_widget_modify_font (labelshow[i],pango_font_description_from_string ("Monospace 18"));
                          gtk_widget_show(labelshow[i]);
                          i++;
                          if (i==9)
                          j++;
                          }
     //rikhtane first data dar data
     
     
     

    int ctr;
    int rnd=rand()%counter;
    for(ctr=0;ctr<counter;ctr++)
    {
    swap(&num[ctr],&num[rnd]);
    labelswap(labelshow[ctr] , labelshow[rnd]);
    }

}
void GenerateItemActivated(GtkWidget *widget , gpointer data ) 
{

    combo = gtk_entry_get_text (GTK_ENTRY (GTK_COMBO (combobox)->entry));
    if (strlen(combo)==11) 
    BubbleSort(widget, NULL);
    if (strlen(combo)==23) 
    BubbleSortD(widget, NULL);
    if (strlen(combo)==14) 
    SelectionSort(widget, NULL);
    if (strlen(combo)==26)
    SelectionSortD(widget, NULL);
    if (strlen(combo)==15) 
    InsertionSort(widget, NULL);
    if (strlen(combo)==27) 
    InsertionSortD(widget, NULL);
    if (strlen(combo)==10) 
    QuickSort(widget, NULL);
    if (strlen(combo)==22) 
    QuickSortD(widget, NULL);
   


                                                                    

}
void fileSaveMenuItemActivated(GtkWidget * widget, gpointer data)
{
	if(strcmp(path,"") == 0)
		fileSaveAsMenuItemActivated(widget,data);
	else
	{
		GtkTextBuffer *buffer = gtk_text_view_get_buffer(textview);

		GtkTextIter start,end;
        gtk_text_buffer_get_start_iter(buffer,&start);
        gtk_text_buffer_get_end_iter(buffer,&end);

        gchar * contents = gtk_text_buffer_get_text(buffer,&start,&end,FALSE);
        if(g_file_set_contents(path,contents,-1,NULL))
        	isChanged = FALSE;
        g_free(contents);
	}
}

void fileSaveAsMenuItemActivated(GtkWidget * widget, gpointer data)
{
	GtkFileChooserDialog * fDialog = gtk_file_chooser_dialog_new("Save file as",window,GTK_FILE_CHOOSER_ACTION_SAVE, GTK_STOCK_CANCEL , GTK_RESPONSE_CANCEL,
    GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,NULL);
	gtk_file_chooser_set_do_overwrite_confirmation(fDialog, TRUE);
	gint res = gtk_dialog_run(fDialog);
	gchar * filename  = gtk_file_chooser_get_filename(fDialog);
	gtk_widget_destroy (fDialog);
	if(res != GTK_RESPONSE_ACCEPT)
		return;

	strcpy(path,filename);
	g_free(filename);
	fileSaveMenuItemActivated(widget,data);
}

void fileQuitMenuItemActivated(GtkWidget * widget, gpointer data)
{
	fileNewMenuItemActivated(widget,data);
	gtk_main_quit();
}


void helpAboutMenuItemActivated(GtkWidget * widget, gpointer data)
{
	GtkAboutDialog * aDialog = gtk_about_dialog_new();
	gtk_about_dialog_set_program_name(aDialog,"First Project");
	gtk_about_dialog_set_version(aDialog,"1.0");
	gtk_about_dialog_set_comments(aDialog,"You can sort your data with this program , thanks to mr.shamsaie's sample editor.");
	gchar **authors[2] = {"Hadi Modares","Vahid Geraee nejad"};
	gtk_about_dialog_set_authors(aDialog,authors);
	gtk_dialog_run(aDialog);
	gtk_widget_destroy (aDialog);
}

void bufferChanged(GtkWidget * widget, gpointer data)
{
	isChanged  = TRUE;
}
void OpenInNewWindow(GtkWidget *widget , gpointer data)
{
     /*
    GenerateItemActivated(widget , NULL );
    static GtkWidget *swindow;
    GtkWidget *scrolled_window;
    GtkWidget *table;
    int i=0;
    int j=0;
    int b;
    gtk_window_set_title (GTK_WINDOW (swindow), "Sort procces");
    swindow = gtk_dialog_new ();
    gtk_container_set_border_width (GTK_CONTAINER (swindow), 0);
    gtk_widget_set_size_request (swindow, 550, 300);
    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 10);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	gtk_window_set_position(GTK_WINDOW(swindow), GTK_WIN_POS_CENTER);
	gtk_box_pack_start (GTK_BOX (GTK_DIALOG(swindow)->vbox), scrolled_window,TRUE, TRUE, 0);
	gtk_widget_show (scrolled_window);
	Print = gtk_button_new_with_label("Print");
    BackwardShow = gtk_button_new_with_label("Backward Show");
    Previous = gtk_button_new_with_label("Previous");
    Next = gtk_button_new_with_label("Next");
    ForwardShow = gtk_button_new_with_label("Forward Show"); 
	gtk_widget_show(Print);
	gtk_widget_show(BackwardShow);
	gtk_widget_show(Previous);
	gtk_widget_show(Next);
	gtk_widget_show(ForwardShow);
	table = gtk_table_new (10, 10, FALSE);
	gtk_table_set_row_spacings (GTK_TABLE (table), 10);
    gtk_table_set_col_spacings (GTK_TABLE (table), 10);
    gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolled_window), table);
    while(i<counter)
	{
                          b=i%10;
                          labelshow[i]=gtk_label_new(firstdata[i]);
                          gtk_table_attach_defaults(GTK_TABLE (table), labelshow[i],b, b+1, j, j+1);
                          gtk_widget_modify_font (labelshow[i],pango_font_description_from_string ("Monospace 18"));
                          gtk_widget_show(labelshow[i]);
                          i++;
                          if (i==9)
                          j++;
                          }
     GTK_WIDGET_SET_FLAGS (Print, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (BackwardShow, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (Previous, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (Next, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (ForwardShow, GTK_CAN_DEFAULT);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), Print,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), BackwardShow,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), Previous,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), Next,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), ForwardShow,TRUE, TRUE, 0);
     gtk_widget_grab_default (Print);
     gtk_widget_grab_default (BackwardShow);
     gtk_widget_grab_default (Previous);
     gtk_widget_grab_default (Next);
     gtk_widget_grab_default (ForwardShow);
     gtk_widget_show (table);
     gtk_widget_show (swindow);
     */
}
void swap(int *aptr,int *bptr)
{               //swap start  
     int hold;
      hold=*aptr;
     *aptr=*bptr;
     *bptr=hold;
}
void bubblegen(int a[], int size)
{  
                //bubblegen start
     int i,j;
     for(i=0;i<size-1;i++){                    //for 1 start
     for(j=0;j<size-1;j++){                    //for 2 start
     if(a[j]>a[j+1]){                          //if start
     swap(&a[j],&a[j+1]);
     
     }                                         //end if
     
     }
     }
}
void BubbleSort(GtkWidget * widget, gpointer data)
{
     GtkTextBuffer *buffer = gtk_text_view_get_buffer(textview);

    GtkTextIter start,end;
    gtk_text_buffer_get_start_iter(buffer , &start);
    gtk_text_buffer_get_end_iter(buffer , &end);
    gchar *contents = gtk_text_buffer_get_text(buffer, &start , &end , FALSE) ;
    counter = 1;
    int i;
	for( i=0;i<strlen(contents);i++)
		if(contents[i]==',')
			counter++;
    
    firstdata=malloc(counter* sizeof(char *));
    labelshow=malloc(counter* sizeof(GtkWidget));
	char *text=strtok(contents,",");

	i = 0;

	while(text!=NULL)
    {

		firstdata[i]=text;

		i++;

		text=strtok(NULL,",");

	}     
	    num = malloc(counter* sizeof(int));
    for(i=0 ; i<counter ; i++)
    {
            int a = atoi( firstdata[i] );
            num[i] = a;
            }
    GtkWidget *scrolled_window;
    GtkWidget *table;
    i=0;
    int j=0;
    int b;
    entrygo = gtk_entry_new ();
    entrygoamount = gtk_entry_get_text (GTK_ENTRY(entrygo));
    go = gtk_button_new_with_label ("Go To");
    gtk_window_set_title (GTK_WINDOW (swindow), "Sort procces");
    swindow = gtk_dialog_new ();
    gtk_container_set_border_width (GTK_CONTAINER (swindow), 0);
    gtk_widget_set_size_request (swindow, 1220, 300);
    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 10);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	gtk_window_set_position(GTK_WINDOW(swindow), GTK_WIN_POS_CENTER);
	gtk_box_pack_start (GTK_BOX (GTK_DIALOG(swindow)->vbox), scrolled_window,TRUE, TRUE, 0);
	gtk_widget_show (scrolled_window);
	Print = gtk_button_new_with_label("Print");
    BackwardShow = gtk_button_new_with_label("Backward Show");
    Previous = gtk_button_new_with_label("Previous");
    Next = gtk_button_new_with_label("Next");
    ForwardShow = gtk_button_new_with_label("Forward Show"); 
	gtk_widget_show(Print);
	gtk_widget_show(BackwardShow);
	gtk_widget_show(Previous);
	gtk_widget_show(Next);
	gtk_widget_show(ForwardShow);
	gtk_widget_show(go);
	gtk_widget_show(entrygo);
	table = gtk_table_new (10, 10, FALSE);
	gtk_table_set_row_spacings (GTK_TABLE (table), 10);
    gtk_table_set_col_spacings (GTK_TABLE (table), 10);
    gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolled_window), table);
       i=0;
   j=0;
    while(i<counter)
	{
                          b=i%10;
                          labelshow[i]=gtk_label_new(firstdata[i]);
                          gtk_table_attach_defaults(GTK_TABLE (table), labelshow[i],b, b+1, j, j+1);
                          gtk_widget_modify_font (labelshow[i],pango_font_description_from_string ("Monospace 18"));
                          gtk_widget_show(labelshow[i]);
                          i++;
                          if (i==9)
                          j++;
                          }
     GTK_WIDGET_SET_FLAGS (Print, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (BackwardShow, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (Previous, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (Next, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (ForwardShow, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (go, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (entrygo, GTK_CAN_DEFAULT);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), Print,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), BackwardShow,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), Previous,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), Next,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), ForwardShow,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), go,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), entrygo,TRUE, TRUE, 0);
     gtk_widget_grab_default (Print);
     gtk_widget_grab_default (BackwardShow);
     gtk_widget_grab_default (Previous);
     gtk_widget_grab_default (Next);
     gtk_widget_grab_default (ForwardShow);
     gtk_widget_grab_default (go);
     gtk_widget_grab_default (entrygo);
     gtk_widget_show (table);
     gtk_widget_show (swindow);
     
//     labelswap(labelshow[1], labelshow[2]);


for(i=0;i<counter;i++){                   
     for(j=0;j<counter-1;j++){                    
     if(num[j]>num[j+1]){                            
     swap(&num[j],&num[j+1]);
     labelswap(labelshow[j] , labelshow[j+1]);
     all++;}}}     
      step *pop=malloc(all*sizeof(step));
      step *push=malloc(all*sizeof(step));
for(i=0;i<counter-1;i++){                   
     for(j=0;j<counter-1;j++){                    
     if(num[j]>num[j+1]){
     swap(&num[j],&num[j+1]);
now++;
pop[now].from=num[j];
pop[now].to=num[j+1];
push[now].from=num[j];
push[now].to=num[j+1];
toppu=all;
}}}


  
    

 


     
}
void BubbleSortD(GtkWidget * widget, gpointer data)
{
GtkTextBuffer *buffer = gtk_text_view_get_buffer(textview);

    GtkTextIter start,end;
    gtk_text_buffer_get_start_iter(buffer , &start);
    gtk_text_buffer_get_end_iter(buffer , &end);
    gchar *contents = gtk_text_buffer_get_text(buffer, &start , &end , FALSE) ;
    counter = 1;
    int i;
	for( i=0;i<strlen(contents);i++)
		if(contents[i]==',')
			counter++;
    
    firstdata=malloc(counter* sizeof(char *));
    labelshow=malloc(counter* sizeof(GtkWidget));
	char *text=strtok(contents,",");

	i = 0;

	while(text!=NULL)
    {

		firstdata[i]=text;

		i++;

		text=strtok(NULL,",");

	}     
	    num = malloc(counter* sizeof(int));
    for(i=0 ; i<counter ; i++)
    {
            int a = atoi( firstdata[i] );
            num[i] = a;
            }
    GtkWidget *scrolled_window;
    GtkWidget *table;
    i=0;
    int j=0;
    int b;
    entrygo = gtk_entry_new ();
    entrygoamount = gtk_entry_get_text (GTK_ENTRY(entrygo));
    go = gtk_button_new_with_label ("Go To");
    gtk_window_set_title (GTK_WINDOW (swindow), "Sort procces");
    swindow = gtk_dialog_new ();
    gtk_container_set_border_width (GTK_CONTAINER (swindow), 0);
    gtk_widget_set_size_request (swindow, 1220, 300);
    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 10);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	gtk_window_set_position(GTK_WINDOW(swindow), GTK_WIN_POS_CENTER);
	gtk_box_pack_start (GTK_BOX (GTK_DIALOG(swindow)->vbox), scrolled_window,TRUE, TRUE, 0);
	gtk_widget_show (scrolled_window);
	Print = gtk_button_new_with_label("Print");
    BackwardShow = gtk_button_new_with_label("Backward Show");
    Previous = gtk_button_new_with_label("Previous");
    Next = gtk_button_new_with_label("Next");
    ForwardShow = gtk_button_new_with_label("Forward Show"); 
	gtk_widget_show(Print);
	gtk_widget_show(BackwardShow);
	gtk_widget_show(Previous);
	gtk_widget_show(Next);
	gtk_widget_show(ForwardShow);
	gtk_widget_show(go);
	gtk_widget_show(entrygo);
	table = gtk_table_new (10, 10, FALSE);
	gtk_table_set_row_spacings (GTK_TABLE (table), 10);
    gtk_table_set_col_spacings (GTK_TABLE (table), 10);
    gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolled_window), table);
       i=0;
   j=0;
    while(i<counter)
	{
                          b=i%10;
                          labelshow[i]=gtk_label_new(firstdata[i]);
                          gtk_table_attach_defaults(GTK_TABLE (table), labelshow[i],b, b+1, j, j+1);
                          gtk_widget_modify_font (labelshow[i],pango_font_description_from_string ("Monospace 18"));
                          gtk_widget_show(labelshow[i]);
                          i++;
                          if (i==9)
                          j++;
                          }
     GTK_WIDGET_SET_FLAGS (Print, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (BackwardShow, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (Previous, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (Next, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (ForwardShow, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (go, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (entrygo, GTK_CAN_DEFAULT);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), Print,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), BackwardShow,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), Previous,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), Next,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), ForwardShow,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), go,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), entrygo,TRUE, TRUE, 0);
     gtk_widget_grab_default (Print);
     gtk_widget_grab_default (BackwardShow);
     gtk_widget_grab_default (Previous);
     gtk_widget_grab_default (Next);
     gtk_widget_grab_default (ForwardShow);
     gtk_widget_grab_default (go);
     gtk_widget_grab_default (entrygo);
     gtk_widget_show (table);
     gtk_widget_show (swindow);
     
for(i=0;i<counter;i++){                   
     for(j=0;j<counter-1;j++){                    
     if(num[j]<num[j+1]){                            
     swap(&num[j],&num[j+1]);
     labelswap(labelshow[j] , labelshow[j+1]);
     all++;}}}     
      step *pop=malloc(all*sizeof(step));
      step *push=malloc(all*sizeof(step));
for(i=0;i<counter-1;i++){                   
     for(j=0;j<counter-1;j++){                    
     if(num[j]<num[j+1]){
     swap(&num[j],&num[j+1]);
now++;
pop[now].from=num[j];
pop[now].to=num[j+1];
push[now].from=num[j];
push[now].to=num[j+1];
toppu=all;
}}}
}
                                               //bubblegen end
void SelectionSort(GtkWidget * widget, gpointer data)
{
GtkTextBuffer *buffer = gtk_text_view_get_buffer(textview);

    GtkTextIter start,end;
    gtk_text_buffer_get_start_iter(buffer , &start);
    gtk_text_buffer_get_end_iter(buffer , &end);
    gchar *contents = gtk_text_buffer_get_text(buffer, &start , &end , FALSE) ;
    counter = 1;
    int i;
	for( i=0;i<strlen(contents);i++)
		if(contents[i]==',')
			counter++;
    
    firstdata=malloc(counter* sizeof(char *));
    labelshow=malloc(counter* sizeof(GtkWidget));
	char *text=strtok(contents,",");

	i = 0;

	while(text!=NULL)
    {

		firstdata[i]=text;

		i++;

		text=strtok(NULL,",");

	}     
	    num = malloc(counter* sizeof(int));
    for(i=0 ; i<counter ; i++)
    {
            int a = atoi( firstdata[i] );
            num[i] = a;
            }
    GtkWidget *scrolled_window;
    GtkWidget *table;
    i=0;
    int j=0;
    int b;
    entrygo = gtk_entry_new ();
    entrygoamount = gtk_entry_get_text (GTK_ENTRY(entrygo));
    go = gtk_button_new_with_label ("Go To");
    gtk_window_set_title (GTK_WINDOW (swindow), "Sort procces");
    swindow = gtk_dialog_new ();
    gtk_container_set_border_width (GTK_CONTAINER (swindow), 0);
    gtk_widget_set_size_request (swindow, 1220, 300);
    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 10);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	gtk_window_set_position(GTK_WINDOW(swindow), GTK_WIN_POS_CENTER);
	gtk_box_pack_start (GTK_BOX (GTK_DIALOG(swindow)->vbox), scrolled_window,TRUE, TRUE, 0);
	gtk_widget_show (scrolled_window);
	Print = gtk_button_new_with_label("Print");
    BackwardShow = gtk_button_new_with_label("Backward Show");
    Previous = gtk_button_new_with_label("Previous");
    Next = gtk_button_new_with_label("Next");
    ForwardShow = gtk_button_new_with_label("Forward Show"); 
	gtk_widget_show(Print);
	gtk_widget_show(BackwardShow);
	gtk_widget_show(Previous);
	gtk_widget_show(Next);
	gtk_widget_show(ForwardShow);
	gtk_widget_show(go);
	gtk_widget_show(entrygo);
	table = gtk_table_new (10, 10, FALSE);
	gtk_table_set_row_spacings (GTK_TABLE (table), 10);
    gtk_table_set_col_spacings (GTK_TABLE (table), 10);
    gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolled_window), table);
       i=0;
   j=0;
    while(i<counter)
	{
                          b=i%10;
                          labelshow[i]=gtk_label_new(firstdata[i]);
                          gtk_table_attach_defaults(GTK_TABLE (table), labelshow[i],b, b+1, j, j+1);
                          gtk_widget_modify_font (labelshow[i],pango_font_description_from_string ("Monospace 18"));
                          gtk_widget_show(labelshow[i]);
                          i++;
                          if (i==9)
                          j++;
                          }
     GTK_WIDGET_SET_FLAGS (Print, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (BackwardShow, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (Previous, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (Next, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (ForwardShow, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (go, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (entrygo, GTK_CAN_DEFAULT);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), Print,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), BackwardShow,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), Previous,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), Next,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), ForwardShow,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), go,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), entrygo,TRUE, TRUE, 0);
     gtk_widget_grab_default (Print);
     gtk_widget_grab_default (BackwardShow);
     gtk_widget_grab_default (Previous);
     gtk_widget_grab_default (Next);
     gtk_widget_grab_default (ForwardShow);
     gtk_widget_grab_default (go);
     gtk_widget_grab_default (entrygo);
     gtk_widget_show (table);
     gtk_widget_show (swindow);    
     
 
     
     
     
}
void SelectionSortD(GtkWidget * widget, gpointer data)
{
GtkTextBuffer *buffer = gtk_text_view_get_buffer(textview);

    GtkTextIter start,end;
    gtk_text_buffer_get_start_iter(buffer , &start);
    gtk_text_buffer_get_end_iter(buffer , &end);
    gchar *contents = gtk_text_buffer_get_text(buffer, &start , &end , FALSE) ;
    counter = 1;
    int i;
	for( i=0;i<strlen(contents);i++)
		if(contents[i]==',')
			counter++;
    
    firstdata=malloc(counter* sizeof(char *));
    labelshow=malloc(counter* sizeof(GtkWidget));
	char *text=strtok(contents,",");

	i = 0;

	while(text!=NULL)
    {

		firstdata[i]=text;

		i++;

		text=strtok(NULL,",");

	}     
	    num = malloc(counter* sizeof(int));
    for(i=0 ; i<counter ; i++)
    {
            int a = atoi( firstdata[i] );
            num[i] = a;
            }
    GtkWidget *scrolled_window;
    GtkWidget *table;
    i=0;
    int j=0;
    int b;
    entrygo = gtk_entry_new ();
    entrygoamount = gtk_entry_get_text (GTK_ENTRY(entrygo));
    go = gtk_button_new_with_label ("Go To");
    gtk_window_set_title (GTK_WINDOW (swindow), "Sort procces");
    swindow = gtk_dialog_new ();
    gtk_container_set_border_width (GTK_CONTAINER (swindow), 0);
    gtk_widget_set_size_request (swindow, 1220, 300);
    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 10);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	gtk_window_set_position(GTK_WINDOW(swindow), GTK_WIN_POS_CENTER);
	gtk_box_pack_start (GTK_BOX (GTK_DIALOG(swindow)->vbox), scrolled_window,TRUE, TRUE, 0);
	gtk_widget_show (scrolled_window);
	Print = gtk_button_new_with_label("Print");
    BackwardShow = gtk_button_new_with_label("Backward Show");
    Previous = gtk_button_new_with_label("Previous");
    Next = gtk_button_new_with_label("Next");
    ForwardShow = gtk_button_new_with_label("Forward Show"); 
	gtk_widget_show(Print);
	gtk_widget_show(BackwardShow);
	gtk_widget_show(Previous);
	gtk_widget_show(Next);
	gtk_widget_show(ForwardShow);
	gtk_widget_show(go);
	gtk_widget_show(entrygo);
	table = gtk_table_new (10, 10, FALSE);
	gtk_table_set_row_spacings (GTK_TABLE (table), 10);
    gtk_table_set_col_spacings (GTK_TABLE (table), 10);
    gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolled_window), table);
       i=0;
   j=0;
    while(i<counter)
	{
                          b=i%10;
                          labelshow[i]=gtk_label_new(firstdata[i]);
                          gtk_table_attach_defaults(GTK_TABLE (table), labelshow[i],b, b+1, j, j+1);
                          gtk_widget_modify_font (labelshow[i],pango_font_description_from_string ("Monospace 18"));
                          gtk_widget_show(labelshow[i]);
                          i++;
                          if (i==9)
                          j++;
                          }
     GTK_WIDGET_SET_FLAGS (Print, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (BackwardShow, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (Previous, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (Next, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (ForwardShow, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (go, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (entrygo, GTK_CAN_DEFAULT);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), Print,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), BackwardShow,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), Previous,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), Next,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), ForwardShow,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), go,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), entrygo,TRUE, TRUE, 0);
     gtk_widget_grab_default (Print);
     gtk_widget_grab_default (BackwardShow);
     gtk_widget_grab_default (Previous);
     gtk_widget_grab_default (Next);
     gtk_widget_grab_default (ForwardShow);
     gtk_widget_grab_default (go);
     gtk_widget_grab_default (entrygo);
     gtk_widget_show (table);
     gtk_widget_show (swindow); 
}
void InsertionSort(GtkWidget * widget, gpointer data)
{
GtkTextBuffer *buffer = gtk_text_view_get_buffer(textview);

    GtkTextIter start,end;
    gtk_text_buffer_get_start_iter(buffer , &start);
    gtk_text_buffer_get_end_iter(buffer , &end);
    gchar *contents = gtk_text_buffer_get_text(buffer, &start , &end , FALSE) ;
    counter = 1;
    int i;
	for( i=0;i<strlen(contents);i++)
		if(contents[i]==',')
			counter++;
    
    firstdata=malloc(counter* sizeof(char *));
    labelshow=malloc(counter* sizeof(GtkWidget));
	char *text=strtok(contents,",");

	i = 0;

	while(text!=NULL)
    {

		firstdata[i]=text;

		i++;

		text=strtok(NULL,",");

	}     
	    num = malloc(counter* sizeof(int));
    for(i=0 ; i<counter ; i++)
    {
            int a = atoi( firstdata[i] );
            num[i] = a;
            }
    GtkWidget *scrolled_window;
    GtkWidget *table;
    i=0;
    int j=0;
    int b;
    entrygo = gtk_entry_new ();
    entrygoamount = gtk_entry_get_text (GTK_ENTRY(entrygo));
    go = gtk_button_new_with_label ("Go To");
    gtk_window_set_title (GTK_WINDOW (swindow), "Sort procces");
    swindow = gtk_dialog_new ();
    gtk_container_set_border_width (GTK_CONTAINER (swindow), 0);
    gtk_widget_set_size_request (swindow, 1220, 300);
    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 10);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	gtk_window_set_position(GTK_WINDOW(swindow), GTK_WIN_POS_CENTER);
	gtk_box_pack_start (GTK_BOX (GTK_DIALOG(swindow)->vbox), scrolled_window,TRUE, TRUE, 0);
	gtk_widget_show (scrolled_window);
	Print = gtk_button_new_with_label("Print");
    BackwardShow = gtk_button_new_with_label("Backward Show");
    Previous = gtk_button_new_with_label("Previous");
    Next = gtk_button_new_with_label("Next");
    ForwardShow = gtk_button_new_with_label("Forward Show"); 
	gtk_widget_show(Print);
	gtk_widget_show(BackwardShow);
	gtk_widget_show(Previous);
	gtk_widget_show(Next);
	gtk_widget_show(ForwardShow);
	gtk_widget_show(go);
	gtk_widget_show(entrygo);
	table = gtk_table_new (10, 10, FALSE);
	gtk_table_set_row_spacings (GTK_TABLE (table), 10);
    gtk_table_set_col_spacings (GTK_TABLE (table), 10);
    gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolled_window), table);
       i=0;
   j=0;
    while(i<counter)
	{
                          b=i%10;
                          labelshow[i]=gtk_label_new(firstdata[i]);
                          gtk_table_attach_defaults(GTK_TABLE (table), labelshow[i],b, b+1, j, j+1);
                          gtk_widget_modify_font (labelshow[i],pango_font_description_from_string ("Monospace 18"));
                          gtk_widget_show(labelshow[i]);
                          i++;
                          if (i==9)
                          j++;
                          }
     GTK_WIDGET_SET_FLAGS (Print, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (BackwardShow, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (Previous, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (Next, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (ForwardShow, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (go, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (entrygo, GTK_CAN_DEFAULT);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), Print,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), BackwardShow,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), Previous,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), Next,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), ForwardShow,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), go,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), entrygo,TRUE, TRUE, 0);
     gtk_widget_grab_default (Print);
     gtk_widget_grab_default (BackwardShow);
     gtk_widget_grab_default (Previous);
     gtk_widget_grab_default (Next);
     gtk_widget_grab_default (ForwardShow);
     gtk_widget_grab_default (go);
     gtk_widget_grab_default (entrygo);
     gtk_widget_show (table);
     gtk_widget_show (swindow);     
     
     

     
     
}
void InsertionSortD(GtkWidget * widget, gpointer data)
{
GtkTextBuffer *buffer = gtk_text_view_get_buffer(textview);

    GtkTextIter start,end;
    gtk_text_buffer_get_start_iter(buffer , &start);
    gtk_text_buffer_get_end_iter(buffer , &end);
    gchar *contents = gtk_text_buffer_get_text(buffer, &start , &end , FALSE) ;
    counter = 1;
    int i;
	for( i=0;i<strlen(contents);i++)
		if(contents[i]==',')
			counter++;
    
    firstdata=malloc(counter* sizeof(char *));
    labelshow=malloc(counter* sizeof(GtkWidget));
	char *text=strtok(contents,",");

	i = 0;

	while(text!=NULL)
    {

		firstdata[i]=text;

		i++;

		text=strtok(NULL,",");

	}     
	    num = malloc(counter* sizeof(int));
    for(i=0 ; i<counter ; i++)
    {
            int a = atoi( firstdata[i] );
            num[i] = a;
            }
    GtkWidget *scrolled_window;
    GtkWidget *table;
    i=0;
    int j=0;
    int b;
    entrygo = gtk_entry_new ();
    entrygoamount = gtk_entry_get_text (GTK_ENTRY(entrygo));
    go = gtk_button_new_with_label ("Go To");
    gtk_window_set_title (GTK_WINDOW (swindow), "Sort procces");
    swindow = gtk_dialog_new ();
    gtk_container_set_border_width (GTK_CONTAINER (swindow), 0);
    gtk_widget_set_size_request (swindow, 1220, 300);
    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 10);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	gtk_window_set_position(GTK_WINDOW(swindow), GTK_WIN_POS_CENTER);
	gtk_box_pack_start (GTK_BOX (GTK_DIALOG(swindow)->vbox), scrolled_window,TRUE, TRUE, 0);
	gtk_widget_show (scrolled_window);
	Print = gtk_button_new_with_label("Print");
    BackwardShow = gtk_button_new_with_label("Backward Show");
    Previous = gtk_button_new_with_label("Previous");
    Next = gtk_button_new_with_label("Next");
    ForwardShow = gtk_button_new_with_label("Forward Show"); 
	gtk_widget_show(Print);
	gtk_widget_show(BackwardShow);
	gtk_widget_show(Previous);
	gtk_widget_show(Next);
	gtk_widget_show(ForwardShow);
	gtk_widget_show(go);
	gtk_widget_show(entrygo);
	table = gtk_table_new (10, 10, FALSE);
	gtk_table_set_row_spacings (GTK_TABLE (table), 10);
    gtk_table_set_col_spacings (GTK_TABLE (table), 10);
    gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolled_window), table);
       i=0;
   j=0;
    while(i<counter)
	{
                          b=i%10;
                          labelshow[i]=gtk_label_new(firstdata[i]);
                          gtk_table_attach_defaults(GTK_TABLE (table), labelshow[i],b, b+1, j, j+1);
                          gtk_widget_modify_font (labelshow[i],pango_font_description_from_string ("Monospace 18"));
                          gtk_widget_show(labelshow[i]);
                          i++;
                          if (i==9)
                          j++;
                          }
     GTK_WIDGET_SET_FLAGS (Print, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (BackwardShow, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (Previous, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (Next, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (ForwardShow, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (go, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (entrygo, GTK_CAN_DEFAULT);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), Print,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), BackwardShow,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), Previous,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), Next,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), ForwardShow,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), go,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), entrygo,TRUE, TRUE, 0);
     gtk_widget_grab_default (Print);
     gtk_widget_grab_default (BackwardShow);
     gtk_widget_grab_default (Previous);
     gtk_widget_grab_default (Next);
     gtk_widget_grab_default (ForwardShow);
     gtk_widget_grab_default (go);
     gtk_widget_grab_default (entrygo);
     gtk_widget_show (table);
     gtk_widget_show (swindow); 
}
void QuickSort(GtkWidget * widget, gpointer data)
{
GtkTextBuffer *buffer = gtk_text_view_get_buffer(textview);

    GtkTextIter start,end;
    gtk_text_buffer_get_start_iter(buffer , &start);
    gtk_text_buffer_get_end_iter(buffer , &end);
    gchar *contents = gtk_text_buffer_get_text(buffer, &start , &end , FALSE) ;
    counter = 1;
    int i;
	for( i=0;i<strlen(contents);i++)
		if(contents[i]==',')
			counter++;
    
    firstdata=malloc(counter* sizeof(char *));
    labelshow=malloc(counter* sizeof(GtkWidget));
	char *text=strtok(contents,",");

	i = 0;

	while(text!=NULL)
    {

		firstdata[i]=text;

		i++;

		text=strtok(NULL,",");

	}     
	    num = malloc(counter* sizeof(int));
    for(i=0 ; i<counter ; i++)
    {
            int a = atoi( firstdata[i] );
            num[i] = a;
            }
    GtkWidget *scrolled_window;
    GtkWidget *table;
    i=0;
    int j=0;
    int b;
    entrygo = gtk_entry_new ();
    entrygoamount = gtk_entry_get_text (GTK_ENTRY(entrygo));
    go = gtk_button_new_with_label ("Go To");
    gtk_window_set_title (GTK_WINDOW (swindow), "Sort procces");
    swindow = gtk_dialog_new ();
    gtk_container_set_border_width (GTK_CONTAINER (swindow), 0);
    gtk_widget_set_size_request (swindow, 1220, 300);
    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 10);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	gtk_window_set_position(GTK_WINDOW(swindow), GTK_WIN_POS_CENTER);
	gtk_box_pack_start (GTK_BOX (GTK_DIALOG(swindow)->vbox), scrolled_window,TRUE, TRUE, 0);
	gtk_widget_show (scrolled_window);
	Print = gtk_button_new_with_label("Print");
    BackwardShow = gtk_button_new_with_label("Backward Show");
    Previous = gtk_button_new_with_label("Previous");
    Next = gtk_button_new_with_label("Next");
    ForwardShow = gtk_button_new_with_label("Forward Show"); 
	gtk_widget_show(Print);
	gtk_widget_show(BackwardShow);
	gtk_widget_show(Previous);
	gtk_widget_show(Next);
	gtk_widget_show(ForwardShow);
	gtk_widget_show(go);
	gtk_widget_show(entrygo);
	table = gtk_table_new (10, 10, FALSE);
	gtk_table_set_row_spacings (GTK_TABLE (table), 10);
    gtk_table_set_col_spacings (GTK_TABLE (table), 10);
    gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolled_window), table);
       i=0;
   j=0;
    while(i<counter)
	{
                          b=i%10;
                          labelshow[i]=gtk_label_new(firstdata[i]);
                          gtk_table_attach_defaults(GTK_TABLE (table), labelshow[i],b, b+1, j, j+1);
                          gtk_widget_modify_font (labelshow[i],pango_font_description_from_string ("Monospace 18"));
                          gtk_widget_show(labelshow[i]);
                          i++;
                          if (i==9)
                          j++;
                          }
     GTK_WIDGET_SET_FLAGS (Print, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (BackwardShow, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (Previous, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (Next, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (ForwardShow, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (go, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (entrygo, GTK_CAN_DEFAULT);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), Print,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), BackwardShow,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), Previous,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), Next,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), ForwardShow,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), go,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), entrygo,TRUE, TRUE, 0);
     gtk_widget_grab_default (Print);
     gtk_widget_grab_default (BackwardShow);
     gtk_widget_grab_default (Previous);
     gtk_widget_grab_default (Next);
     gtk_widget_grab_default (ForwardShow);
     gtk_widget_grab_default (go);
     gtk_widget_grab_default (entrygo);
     gtk_widget_show (table);
     gtk_widget_show (swindow);  
     quicksort(num , num[0] , num[counter - 1]);

          
}





void QuickSortD(GtkWidget * widget, gpointer data)
{
GtkTextBuffer *buffer = gtk_text_view_get_buffer(textview);

    GtkTextIter start,end;
    gtk_text_buffer_get_start_iter(buffer , &start);
    gtk_text_buffer_get_end_iter(buffer , &end);
    gchar *contents = gtk_text_buffer_get_text(buffer, &start , &end , FALSE) ;
    counter = 1;
    int i;
	for( i=0;i<strlen(contents);i++)
		if(contents[i]==',')
			counter++;
    
    firstdata=malloc(counter* sizeof(char *));
    labelshow=malloc(counter* sizeof(GtkWidget));
	char *text=strtok(contents,",");

	i = 0;

	while(text!=NULL)
    {

		firstdata[i]=text;

		i++;

		text=strtok(NULL,",");

	}     
	    num = malloc(counter* sizeof(int));
    for(i=0 ; i<counter ; i++)
    {
            int a = atoi( firstdata[i] );
            num[i] = a;
            }
    GtkWidget *scrolled_window;
    GtkWidget *table;
    i=0;
    int j=0;
    int b;
    entrygo = gtk_entry_new ();
    entrygoamount = gtk_entry_get_text (GTK_ENTRY(entrygo));
    go = gtk_button_new_with_label ("Go To");
    gtk_window_set_title (GTK_WINDOW (swindow), "Sort procces");
    swindow = gtk_dialog_new ();
    gtk_container_set_border_width (GTK_CONTAINER (swindow), 0);
    gtk_widget_set_size_request (swindow, 1220, 300);
    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 10);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	gtk_window_set_position(GTK_WINDOW(swindow), GTK_WIN_POS_CENTER);
	gtk_box_pack_start (GTK_BOX (GTK_DIALOG(swindow)->vbox), scrolled_window,TRUE, TRUE, 0);
	gtk_widget_show (scrolled_window);
	Print = gtk_button_new_with_label("Print");
    BackwardShow = gtk_button_new_with_label("Backward Show");
    Previous = gtk_button_new_with_label("Previous");
    Next = gtk_button_new_with_label("Next");
    ForwardShow = gtk_button_new_with_label("Forward Show"); 
	gtk_widget_show(Print);
	gtk_widget_show(BackwardShow);
	gtk_widget_show(Previous);
	gtk_widget_show(Next);
	gtk_widget_show(ForwardShow);
	gtk_widget_show(go);
	gtk_widget_show(entrygo);
	table = gtk_table_new (10, 10, FALSE);
	gtk_table_set_row_spacings (GTK_TABLE (table), 10);
    gtk_table_set_col_spacings (GTK_TABLE (table), 10);
    gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolled_window), table);
       i=0;
   j=0;
    while(i<counter)
	{
                          b=i%10;
                          labelshow[i]=gtk_label_new(firstdata[i]);
                          gtk_table_attach_defaults(GTK_TABLE (table), labelshow[i],b, b+1, j, j+1);
                          gtk_widget_modify_font (labelshow[i],pango_font_description_from_string ("Monospace 18"));
                          gtk_widget_show(labelshow[i]);
                          i++;
                          if (i==9)
                          j++;
                          }
     GTK_WIDGET_SET_FLAGS (Print, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (BackwardShow, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (Previous, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (Next, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (ForwardShow, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (go, GTK_CAN_DEFAULT);
     GTK_WIDGET_SET_FLAGS (entrygo, GTK_CAN_DEFAULT);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), Print,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), BackwardShow,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), Previous,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), Next,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), ForwardShow,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), go,TRUE, TRUE, 0);
     gtk_box_pack_start (GTK_BOX (GTK_DIALOG (swindow)->action_area), entrygo,TRUE, TRUE, 0);
     gtk_widget_grab_default (Print);
     gtk_widget_grab_default (BackwardShow);
     gtk_widget_grab_default (Previous);
     gtk_widget_grab_default (Next);
     gtk_widget_grab_default (ForwardShow);
     gtk_widget_grab_default (go);
     gtk_widget_grab_default (entrygo);
     gtk_widget_show (table);
     gtk_widget_show (swindow);     
}



//sort buttons - functions
void PrintFunc(GtkWidget * widget, gpointer data)
{
     
     
     
     
     }
void BackwardShowFunc(GtkWidget * widget, gpointer data)
{
     
     while(toppu!=0);{
            undo();
            wait(5);}     
         
     }
void PreviousFunc(GtkWidget * widget, gpointer data)
{
          while(toppo!=0);{
            undo();
            wait(5);}
     
     
     }
void NextFunc(GtkWidget * widget, gpointer data)
{
     
     swap(&num[push[toppu].from],&num[push[toppu].to]);
     labelswap(labelshow[push[toppu].from] , labelshow [push[toppu].to]);
     toppu--;
     toppo++;
     
     
     }
void ForwardShowFunc(GtkWidget * widget, gpointer data)
{
          while(toppu!=0);{
            doo();
            wait(5);}
     
     }
void Go(GtkWidget * widget, gpointer data)
{
     int a = atoi (entrygoamount);
     
     toppo=0;
     toppu=all;
     for(i=0;i<counter;i++){                   
            int a = atoi( firstdata[i] );
            num[i] = a;
     }
     for(i=0;i<a;i++){
     doo();}
     
     }
void labelswap(GtkWidget **label1 , GtkWidget **label2)
{
     GtkWidget **a = gtk_label_new( gtk_label_get_text( GTK_LABEL(label1) ) );
     gtk_label_set_text( GTK_LABEL(label1),gtk_label_get_text( GTK_LABEL(label2) ) );
     gtk_label_set_text( GTK_LABEL(label2),gtk_label_get_text( GTK_LABEL(a) ) );
}
void bubble_afza(int num[], int counter){            

     
for(i=0;i<counter;i++){                   
     for(j=0;j<counter-1;j++){                    
     if(num[j]>num[j+1]){                            
     swap(&num[j],&num[j+1]);
     all++;}}}     
      step *pop=malloc(all*sizeof(step));
      step *push=malloc(all*sizeof(step));
for(i=0;i<counter-1;i++){                   
     for(j=0;j<counter-1;j++){                    
     if(num[j]>num[j+1]){
     swap(&num[j],&num[j+1]);
now++;
push[now].from=num[j];
push[now].to=num[j+1];
toppu=all;
}}}}

void doo(){

swap(&num[push[toppu].from],&num[push[toppu].to]);
labelswap(labelshow[push[toppu].from] , labelshow[push[toppu].to] );
toppu--;
toppo++;}




void wait(int z)                             //wait start
{int x = time(0) + 1;
if( z == 1)
{z = z + 2; 
}
else 
{z = z; 
}
int y = z;
for (time(0); x < time(0) + z; )
{if (x == time(0) + 1)
{++x;
--y;
}
if ( y == 0 )
{break;
}
}
}
void undo(){

     
swap(&num[pop[toppo].from],&num[pop[toppo].to]);
labelswap(labelshow[pop[toppo].from] , labelshow [pop[toppo].to] );
toppu++;
toppo--;}

  void quicksort(int array[] , int left , int right){
        if (left < right){
                int middle = partition(array , left , right) ;
                quicksort(array , left , middle-1) ;
                quicksort(array , middle+1 , right);
        }
}
 
int partition(int array[] , int left , int right){
        int middle ;
 
        int x = array[left] ;
        int l = left ;
        int r = right ;
        while(l < r){
                while((array[l] <= x) && (l < right)) l++ ;
                while((array[r] > x) && (r >= left)) r-- ;
                if(l < r){ 
                        int temp = array[l];
                        array[l] = array[r];
                        array[r] = temp ;
                        labelswap(labelshow[l] , labelshow [r]);
                }
        }
        middle = r ;
                int temp = array[left];
                array[left] = array[middle] ;
                array[middle] = temp;
                labelswap(labelshow[left] , labelshow[middle]);
        return middle ;
}
